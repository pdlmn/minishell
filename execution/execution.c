/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:49:14 by omougel           #+#    #+#             */
/*   Updated: 2024/04/02 11:41:36 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define MALLOC_ERROR 

int	is_input(char *redir)
{
	if (!ft_strcmp(redir, "<") || !ft_strcmp(redir, "<<"))
		return (1);
	return (0);
}

int	is_output(char *redir)
{
	if (!ft_strcmp(redir, ">") || !ft_strcmp(redir, ">>"))
		return (1);
	return (0);
}

char	**creat_builtins(void)
{
	char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	return (builtins);
}

int	is_builtin(char *cmd)
{
	char	**builtins;
	int		i;

	builtins = creat_builtins();
	i = 0;
	while (builtins[i])
		if (!ft_strcmp(cmd, builtins[i++]))
			return (1);
	return (0);
}

int	is_there_pipe(char ***cmd_tab)
{
	size_t	i;

	i = 0;
	while (cmd_tab && cmd_tab[i])
		if (!ft_strcmp("|", cmd_tab[i++][0]))
			return (1);
	return (0);
}

int	here_doc(char *lim)
{
	char	*buffer;
	int		fd[2];

	buffer = get_next_line(STDIN_FILENO);
	if (pipe(fd) == -1)
		return (EXIT_FAILURE); //TODO ERROR
	while (buffer && ft_strcmp(buffer, lim))
	{
		write(fd[1], buffer, ft_strlen(buffer)); //deal with error case maybe
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
	return (fd[0]);
}

int	redir_input(char *infile)
{
	return (open(infile, O_RDONLY, 0644));
}

int	redir_output(char *outfile)
{
	return (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	append_output(char *outfile)
{
	return (open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

void  ft_exit(void)
{
	perror(NULL); //try to put the correct error message
	exit(errno);
}

char  **replacefront(char **cmd, char *path)
{
	free(cmd[0]);
	cmd[0] = path;
	return (cmd);
}

char	**split_envp(char **envp)
{
	char	**env;
	size_t	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
		i++;
	if (!envp[i])
		return (ft_putstr_fd("No PATH in environement\n", 2), NULL);
	env = ft_split(&envp[i][5], ':');
	if (!env)
		return (NULL);
	return (env);
}

char	**find_command(char **cmd, char **envp)
{
	size_t	i;
	char	*tmp;
	char	**env;

	i = 0;
	if (is_builtin(cmd[0]))
		return (cmd);//do builtins
	if (!access(cmd[0], X_OK))
		return (cmd);
	env = split_envp(envp);
	while (env && env[i])
	{
		tmp = ft_strjoin(env[i], cmd[0]);
		if (!tmp)
			return (NULL); //TODO MALLOC_ERROR
		if (!access(tmp, X_OK))
			return (replacefront(cmd, tmp));
		free(tmp);
		i++;
	}
	return (NULL); //TODO ERROR CMD NOT FOUND
}

void	exec_cmd(char **cmd, int fd_in, int fd_out, char **envp)
{
	cmd = find_command(cmd, envp);
	if (cmd && *cmd)
	{
		if (dup2(fd_in, STDIN_FILENO) < 0)
			ft_exit();
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			ft_exit();
		close(fd_in);
		close(fd_out);
		execve(cmd[0], cmd, envp);
	}
	else
	{
		close(fd_in);
		close(fd_out);
	}
	ft_free_split(cmd); // do i need to free here in the child so that there are no leaks ??
	exit(errno);
}

char	***fork_and_execute(char ***cmd_tab, int *fd_in, char **envp)
{
	int		fd[2];
	int		pid;
	size_t	i;
	int		fd_out;

	fd[0] = -1;
	fd[1] = -1;
	i = 0;
	fd_out = 1;
	if (is_there_pipe(cmd_tab))
		if (pipe(fd) == -1)
			return (NULL); //TODO error
	while (cmd_tab[i] && ft_strcmp(cmd_tab[i][0], "|"))
	{
		if (is_input(cmd_tab[i][0]))
		{
			if (*fd_in != 0)
				close(*fd_in);
			if (!ft_strcmp(cmd_tab[i][0], "<"))
				*fd_in = redir_input(cmd_tab[i][1]);
			else
				*fd_in = here_doc(cmd_tab[i][1]);
		}
		else if (is_output(cmd_tab[i][0]))
		{
			if (fd_out != 1)
				close(fd_out);
			if (!ft_strcmp(cmd_tab[i][0], ">"))
				fd_out = redir_output(cmd_tab[i][1]);
			else
				fd_out = append_output(cmd_tab[i][1]);
		}
		else
		{
			if (fd_in >= 0 && fd_out > 0)
			{
				if (fd_out == 1 && fd[1] > 0)
					fd_out = fd[1];
				else if (fd[1] > 0)
					close(fd[1]);
				pid = fork(); //TODO error case of fork
				if (pid == 0)
				{
					close(fd[0]);
					exec_cmd(cmd_tab[i], *fd_in, fd_out, envp);
				}
			}
			else
				return (&cmd_tab[i + 1]); //TODO ERROR INVALID FILE DESCRIPTOR
		}
		i++;
	}
	if (fd_in > 0)
		close(*fd_in);
	if (fd_out > 1)
		close(fd_out);
	if (fd[1] > 0)
		close(fd[1]);
	if (fd[0] > 0)
		*fd_in = fd[0];
	if (!cmd_tab || !cmd_tab[i])
		return (NULL);
	return (&cmd_tab[i + 1]);
}

char  ***execution(char ***cmd_tab, int *fd_in)
{
	int	fd[2];
	//int	pid;
	size_t	i;
	int	fd_out;

	fd[0] = -1;
	fd[1] = -1;
	i = 0;
	fd_out = 1;
	if (is_there_pipe(cmd_tab))
		if (pipe(fd) == -1)
			return ERROR; //TODO
	while (cmd_tab[i] && ft_strcmp(cmd_tab[i][0], "|"))
	{
		if (is_input(cmd_tab[i][0]))
		{
			if (*fd_in != 0)
				close(*fd_in);
			if (!ft_strcmp(cmd_tab[i][0], "<"))
				*fd_in = redir_input(cmd_tab[i][1]);
			else
				*fd_in = here_doc(cmd_tab[i][1]);
		}
		else if (is_output(cmd_tab[i][0]))
		{
			if (fd_out != 1)
				close(fd_out);
			if (!ft_strcmp(cmd_tab[i][0], ">"))
				fd_out = redir_output(cmd_tab[i][1]);
			else
				fd_out = append_output(cmd_tab[i][1]);
		}
		else
		{
			if (fd_in >= 0 && fd_out > 0)
				exec_cmd(); // get the pid of the last cmd to deal with return value and also we have to stock it into our new ENVIRONEMENT
			else(ERROR); //TODO
		}
		i++;
	}
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
	if (fd[1] > 0)
		close(fd[1]);
	if (fd[0] > 0)
		*fd_in = fd[0];
	if (!cmd_tab || !cmd_tab[i])
		return (NULL);
	return (&cmd_tab[i + 1]); 
}
