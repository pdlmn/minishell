/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:49:14 by omougel           #+#    #+#             */
/*   Updated: 2024/05/30 16:34:21 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
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

int	calculate_token_list_len(t_tlist *lst)
{
	t_token	*curr;
	int		res;

	curr = lst->head;
	res = 0;
	while (curr)
	{
		res += curr->len;
		res += curr->space_after;
		curr = curr->next;
	}
	return (res);
}

char	*ft_strjoin_cmd(char const *s1, char const *s2)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = '/';
	while (s2 && s2[i - 1 - ft_strlen(s1)])
	{
		dest[i] = s2[i - 1 - ft_strlen(s1)];
		i++;
	}
	return (dest);
}

char	*join_expanded_strings(t_tlist *lst)
{
	t_token	*curr;
	char	*res;
	int		len;
	int		i;
	int		j;

	curr = lst->head;
	len = calculate_token_list_len(lst);
	res = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (curr)
	{
		j = 0;
		while (curr->content[j])
			res[i++] = curr->content[j++];
		if (curr->space_after)
			res[i++] = ' ';
		curr = curr->next;
	}
	res[i] = '\0';
	return (res);
}

char  *expend_heredoc(char *buffer)
{
	t_minishell	  sh;

	lex_heredoc_input(buffer, &sh.lst, DELIM);
	expand_heredoc(&sh, &sh.lst, DELIM);
	buffer = join_expanded_strings(&sh.lst);
	token_list_free(&sh.lst);
	return (buffer);
}

int	here_doc(char *lim, char *quoted)
{
	char  *buffer;
	int	  fd[2];

	buffer = readline(">");
	if (pipe(fd) == -1)
		return (EXIT_FAILURE); // TODO MALLOC ERROR
	while (buffer && ft_strcmp(buffer, lim))
	{
		if (!quoted)
			buffer = expend_heredoc(buffer);
		write(fd[1], buffer, ft_strlen(buffer)); //deal with error case maybe
		write(fd[1], "\n", 1);
		free(buffer);
		buffer = readline(">");
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

void  ft_exit(t_minishell *msh)
{
	token_list_free(&msh->lst);
	ht_free_table(msh->env);
	ft_free_table(msh->cmd_tab);
//	perror(NULL); //try to put the correct error message
	exit(errno);
}

char  **replacefront(char **cmd, char *path)
{
	cmd[0] = path;
	return (cmd);
}

char	**split_envp(t_ht_table *envp) // change with the environement function
{
	char	*tmp;
	char	**env;

	if (!envp)
		return (NULL);
	tmp = ht_get(envp, "PATH");
	if (!tmp)
		return (ft_putstr_fd("No PATH in environement\n", 2), NULL);
	env = ft_split(tmp, ':');
	if (!env)
		return (NULL);
	return (env);
}

char	**find_command(char **cmd, t_minishell sh)
{
	size_t	i;
	char	*tmp;
	char	**env;

	i = 0;
	if (is_builtin(cmd[0]))
		return (cmd);
	if (!ft_strncmp("./", cmd[0], 2) && !access(cmd[0], X_OK))
		return (cmd);
	env = split_envp(sh.env);
	while (env && env[i])
	{
		tmp = ft_strjoin_cmd(env[i], cmd[0]);
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
	errno = 127;
	return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd(": command not found\n", 2), NULL); //TODO ERROR CMD NOT FOUND
}

int	echo_params(char **cmd, int *nl)
{
	int	j;
	int i;

	*nl = 0;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		if (cmd[i][j] == '\0')
			return (i);
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
			*nl = 1;
		else
			break;
		i++;
	}
	return (i);
}

int	echo(char **cmd, t_ht_table *env)
{
	int	nl;
	int i;

	(void)env;
	i = echo_params(cmd, &nl);
	while (cmd[i])
	{
		printf("%s%c", cmd[i], ' ' * (cmd[i + 1] != NULL));
		i++;
	}
	if (nl == 0)
		printf("\n");
	return (0);
}

int	cd(char **cmd, t_ht_table *env)
{

}

int	pwd(char **cmd, t_ht_table *env)
{
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: pwd: invalid option\n", 2), 2);
	printf("%s\n", ht_get(env, "PWD"));//if PWD has been changed need to display the right thing anyway
	return (0);
}

size_t	keylen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=' && str[i] != '+' && str[i])
		i++;
	return (i);
}

size_t	valuelen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (i);
	return (i + 1);
}

int export(char **cmd, t_ht_table *env)
{
	int	i;
	char *key;
	char *value;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: export: invalid option\n", 2), 2);
	while (cmd[++i])
	{
		key = ft_substr(cmd[i], 0, keylen(cmd[i]));
		value = ft_strjoin(ht_get(env, key), &cmd[i][valuelen(cmd[i])]);
		ht_set(env, key, value);
	}
	return (0);
}

int unset(char **cmd, t_ht_table *env)
{
	int	i;

	i = 1;
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: unset: invalid option\n", 2), 2);
	while (cmd[i])
		ht_delete(env, cmd[i++]);
	return (0);
}

int	env(char **cmd, t_ht_table *env)
{
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: env: invalid option\n", 2), 2);
	ht_print_table(env);
	return (0);
}

void  bt_exit(t_minishell *msh)
{
	ft_putstr_fd("exit", 2);
	ft_exit(msh);
}

int	do_builtins(char **cmd, t_ht_table *env, t_minishell *sh) //ameliorer en s'inspirant du printf
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (echo(cmd, env));
	if (!ft_strcmp(cmd[0], "cd"))
		return (cd(cmd, env));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (pwd(cmd, env));
	if (!ft_strcmp(cmd[0], "export"))
		return (export(cmd, env));
	if (!ft_strcmp(cmd[0], "unset"))
		return (unset(cmd, env));
	if (!ft_strcmp(cmd[0], "env"))
		return (env(cmd, env));
	if (!ft_strcmp(cmd[0], "exit"))
		bt_exit(msh);
	return (1);
}

void	exec_cmd(char **cmd, t_minishell msh)
{
	char	**envp;

	if (dup2(msh.fd_in, STDIN_FILENO) < 0)
		ft_exit(&msh);
	if (dup2(msh.fd_out, STDOUT_FILENO) < 0)
		ft_exit(&msh);
	if (msh.fd_in != 0)
		close(msh.fd_in);
	if (msh.fd_out != 1)
		close(msh.fd_out);
	envp = env_ht_to_arr(msh.env);
	if (!access(cmd[0], X_OK))
		execve(cmd[0], cmd, envp);
	else
		errno = do_builtins(cmd, msh.env);
	ft_free_split(cmd); // IN CASE OF ERROR OR COMMAND NOT FOUND THE CHILD NEED TO FREE EVERYTHING INCLUDING LEXER AND COMMAND TABLE 3 STAR AND ENV
	exit(errno);
}

int	check_input(char **input_redir, int fd_in)
{
	if (fd_in != 0)
		close(fd_in);
	if (!ft_strcmp(input_redir[0], "<"))
		fd_in = redir_input(input_redir[1]); // what if wrong redir -1 or error message idk but does it crash ?
	else
		fd_in = here_doc(input_redir[1], input_redir[2]);
	return (fd_in);
}

int	check_output(char **output_redir, int fd_out)
{
	if (fd_out != 1)
		close(fd_out);
	if (!ft_strcmp(output_redir[0], ">"))
		fd_out = redir_output(output_redir[1]);
	else
		fd_out = append_output(output_redir[1]);
	return (fd_out);
}

void	secure_close(int *fd_out, int *fd_in, int *pipe_out, int *pipe_in)
{
	if (*fd_in > 0)
		close(*fd_in);
	if (*fd_out > 1)
		close(*fd_out);
	if (*pipe_in > 0)
		close(*pipe_in);
	if (*pipe_out > 0)
		*fd_in = *pipe_out;
}

int	go_to_next_cmd(char ***cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[i] && ft_strcmp(cmd_tab[i][0], "|"))
		i++;
	return (i);
}

char	***fork_and_execute(t_minishell *msh, int *pid)
{
	int		fd[2];
	size_t	i;
	char	**cmd;

	fd[0] = -1;
	fd[1] = -1;
	i = 0;
	msh->fd_out = 1;	
	*pid = -1;
	if (is_there_pipe(msh->cmd_tab))
		if (pipe(fd) == -1)
			return (NULL); //TODO error
	*pid = fork(); //TODO error case of fork check -1
	if (*pid == 0)
	{
		while (msh->cmd_tab[i] && ft_strcmp(msh->cmd_tab[i][0], "|")) // modified ft_strcmp from libft
		{
			if (is_input(msh->cmd_tab[i][0]))
				msh->fd_in = check_input(msh->cmd_tab[i], msh->fd_in);
			else if (is_output(msh->cmd_tab[i][0]))
				msh->fd_out = check_output(msh->cmd_tab[i], msh->fd_out);
			else
			{
				if (msh->fd_in >= 0 && msh->fd_out > 0)
				{
					if (msh->fd_out == 1 && fd[1] > 0)
						msh->fd_out = fd[1];
					else if (fd[1] > 0)
						close(fd[1]);
					cmd = find_command(msh->cmd_tab[i], *msh);
					if (cmd && *cmd)
					{
						if (fd[0] > 0)
							close(fd[0]);
						exec_cmd(msh->cmd_tab[i], *msh);
						free(cmd[0]);
					}
					secure_close(&msh->fd_out, &msh->fd_in, &fd[0], &fd[1]);
					ft_exit(msh);
				}
				secure_close(&msh->fd_out, &msh->fd_in, &fd[0], &fd[1]);
				ft_exit(msh);
			//		return (&msh->cmd_tab[i + 1]); //TODO ERROR INVALID FILE DESCRIPTOR and don't return exit
			}
			i++;
		}
	}
	i = go_to_next_cmd(msh->cmd_tab);
	secure_close(&msh->fd_out, &msh->fd_in, &fd[0], &fd[1]);
	if (!msh->cmd_tab || !msh->cmd_tab[i])
		return (NULL);
	return (&msh->cmd_tab[i + 1]);
}

int  execute(t_minishell msh)
{
	int	num_of_child;

	msh.fd_in = 0;
//	msh.last_status= -1;
	num_of_child = count_pipe(msh.lst.head);
	while (msh.cmd_tab && msh.cmd_tab[0])
		msh.cmd_tab = fork_and_execute(&msh, &msh.pid);
	if (msh.pid > 0)
		waitpid(msh.pid, &msh.last_status, 0);
	while (num_of_child-- > 0)
		wait(NULL);
	return (WEXITSTATUS(msh.last_status)); // put last status code with the function to the environement
}
