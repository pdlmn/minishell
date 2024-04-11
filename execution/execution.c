/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:49:14 by omougel           #+#    #+#             */
/*   Updated: 2024/04/11 10:07:18 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MALLOC_ERROR 

char ***command_table(t_token *lst);
void  ft_free_table(char ***tab);

size_t	ft_count_child(char ***cmd_tab)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (cmd_tab && cmd_tab[i] && cmd_tab[i][0])
	{
		if (!ft_strcmp(cmd_tab[i][0], "|"))
			count++;
		i++;
	}
	return (count);
}

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
	char	**builtins;

	builtins = malloc(8 * sizeof(char *));
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
	{
		if (!ft_strcmp(cmd, builtins[i++]))
		{
			free(builtins);
			return (1);
		}
	}
	free(builtins);
	return (0);
}

int	is_there_pipe(char ***cmd_tab)
{
	size_t	i;

	i = 0;
	while (cmd_tab && cmd_tab[i] && cmd_tab[i][0])
		if (!ft_strcmp("|", cmd_tab[i++][0]))
			return (1);
	return (0);
}

int	is_lim(char *buffer, char *lim)
{
	buffer[ft_strlen(buffer) - 1] = '\0';
	if (!ft_strcmp(buffer, lim))
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
	while (buffer && !is_lim(buffer, lim))
	{
		write(fd[1], buffer, ft_strlen(buffer)); //deal with error case maybe
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
	}
	free(buffer);
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
	char	*buff;
	char	**env;

	i = 0;
	if (is_builtin(cmd[0]))
		return (cmd);//do builtins
	if (!access(cmd[0], X_OK))
		return (cmd);
	env = split_envp(envp);
	while (env && env[i])
	{
		buff = ft_strjoin(env[i], "/");//this
		tmp = ft_strjoin(buff, cmd[0]);//or modify ft_strjoin
		free(buff);
		if (!tmp)
			return (NULL); //TODO MALLOC_ERROR
		if (!access(tmp, X_OK))
		{
			ft_free_split(env);
			return (replacefront(cmd, tmp));
		}
		free(tmp);
		i++;
	}
	ft_free_split(env); //add some other free env in the upper code to deal with error cases 
	return (ft_putstr_fd("command not found", 2), NULL); //TODO ERROR CMD NOT FOUND
}

void	exec_cmd(char **cmd, int fd_in, int fd_out, char **envp)
{
	if (dup2(fd_in, STDIN_FILENO) < 0)
		ft_exit();
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		ft_exit();
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
	execve(cmd[0], cmd, envp);
	ft_free_split(cmd); // IN CASE OF ERROR OR COMMAND NOT FOUND THE CHILD NEED TO FREE EVERYTHING INCLUDING LEXER AND COMMAND TABLE 3 STAR
	exit(errno);
}

char	***fork_and_execute(char ***cmd_tab, int *fd_in, char **envp, int *pid)
{
	int		fd[2];
	size_t	i;
	int		fd_out;
	char	**cmd;

	fd[0] = -1;
	fd[1] = -1;
	i = 0;
	fd_out = 1;
	*pid = -1;
	if (is_there_pipe(cmd_tab))
		if (pipe(fd) == -1)
			return (NULL); //TODO error
	while (cmd_tab[i] && cmd_tab[i][0] && ft_strcmp(cmd_tab[i][0], "|"))
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
			if (*fd_in >= 0 && fd_out > 0)
			{
				if (fd_out == 1 && fd[1] > 0)
					fd_out = fd[1];
				else if (fd[1] > 0)
					close(fd[1]);
				cmd = find_command(cmd_tab[i], envp);
				if (cmd && *cmd)
				{
					*pid = fork(); //TODO error case of fork check -1
					if (*pid == 0)
					{
						if (fd[0] > 0)
							close(fd[0]);
						exec_cmd(cmd_tab[i], *fd_in, fd_out, envp);
					}
					if (cmd[0] != cmd_tab[i][0])
						free(cmd[0]);
				}
			}
			else
				return (&cmd_tab[i + 1]); //TODO ERROR INVALID FILE DESCRIPTOR
		}
		i++;
	}
	if (*fd_in > 0)
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

int  execute(char ***cmd_tab, char **envp)
{
	int	fd_in;
	int	pid;
	int status;
	int	num_of_child;

	fd_in = 0;
	status = -1;
	num_of_child = ft_count_child(cmd_tab);
	while (cmd_tab && *cmd_tab)
		cmd_tab = fork_and_execute(cmd_tab, &fd_in, envp, &pid);
	if (pid > 0)
		waitpid(pid, &status, 0);
	while (num_of_child-- > 0)
		wait(NULL);
	return (WEXITSTATUS(status));
}

void	print_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		ft_printf("%s ", arr[i++]);
	ft_printf("\n");
}
/*
void  new_token_list_free(t_token *token)
{
	t_token *curr;
	t_token *tmp;

	curr = token;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}*/

int main(int argc, char **argv, char **envp)
{
	t_token	*lst;
	char	***cmd_tab;
	int		status;

	if (argc != 2)
		return (0);
/*	lst = lexer("echo <\"hello\"  >>>| \"\"\"''\"'hello'\"''\"\"\" | asdasda \
zxc <<qw|a \"QUOTED AGAIN A\" 'small quote'");*/
	lst = lexer(argv[1]);
//	token_list_print(lst);
//	ft_printf("\n\n\n\n");
	cmd_tab = command_table(lst);
	if (!cmd_tab)
		return (EXIT_FAILURE); // don't return yet deal with previous malloc fail and free if necesary
//	while (cmd_tab && cmd_tab[i])
//		print_arr(cmd_tab[i++]);
	status = execute(cmd_tab, envp);
	token_list_free(lst);
	ft_free_table(cmd_tab);
	return (status);
}
