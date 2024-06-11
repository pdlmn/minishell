/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:46:09 by omougel           #+#    #+#             */
/*   Updated: 2024/06/11 16:06:48 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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
	if (is_builtin(cmd[0]))
	{
		do_builtins(cmd, msh.env, &msh);
		errno = set_or_get_exit_status(GET, -1);
	}
	if (!access(cmd[0], X_OK))
		execve(cmd[0], cmd, envp);
	ft_free_split(cmd);
	exit(errno);
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

char	**replacefront(char **cmd, char *path)
{
	free(cmd[0]);
	cmd[0] = path;
	return (cmd);
}
