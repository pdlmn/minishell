/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:49:14 by omougel           #+#    #+#             */
/*   Updated: 2024/06/11 16:16:56 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	go_to_next_pipe(char ***cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[i] && ft_strcmp(cmd_tab[i][0], "|"))
		i++;
	return (i);
}

void	check_cmd(t_minishell *msh, int *fd, int i)
{
	char	**cmd;

	if (msh->fd_in >= 0 && msh->fd_out > 0)
	{
		cmd = find_command(msh->cmd_tab[i], msh);
		if (cmd && *cmd)
		{
			if (fd[0] > 0)
				close(fd[0]);
			exec_cmd(msh->cmd_tab[i], *msh);
			free(cmd[0]);
		}
	}
	if (!is_builtin(msh->cmd_tab[i][0]))
	{
		secure_close(&msh->fd_out, &msh->fd_in, &fd[0], &fd[1]);
		ft_exit(msh);
	}
}

t_minishell	*read_cmd(t_minishell *msh, int *fd, int *pid)
{
	int	i;

	i = 0;
	while (msh->cmd_tab[i] && ft_strcmp(msh->cmd_tab[i][0], "|"))
	{
		if (is_input(msh->cmd_tab[i][0]))
			msh->fd_in = check_input(msh->cmd_tab[i], msh->fd_in);
		else if (is_output(msh->cmd_tab[i][0]))
			msh->fd_out = check_output(msh->cmd_tab[i], msh->fd_out);
		else if (msh->cmd_tab[i][0])
			check_cmd(msh, fd, i);
		if (msh->fd_in == -1 || msh->fd_out == -1)
		{
			perror(msh->cmd_tab[i][1]);
			if (is_builtin(msh->cmd_tab[i][0]))
				break ;
			secure_close(&msh->fd_out, &msh->fd_in, &fd[0], &fd[1]);
			ft_exit(msh);
		}
		i++;
	}
	if (*pid == 0)
		ft_exit(msh);
	return (msh);
}

char	***fork_and_execute(t_minishell *msh, int *pid)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	msh->fd_out = 1;
	*pid = -1;
	if (is_there_pipe(msh->cmd_tab))
	{
		if (pipe(fd) == -1)
			return (NULL);
		msh->fd_out = fd[1];
	}
	if (is_builtin(msh->cmd_tab[go_to_next_pipe(msh->cmd_tab) - 1][0]))
		read_cmd(msh, fd, pid);
	else
	{
		init_exec_signal_handlers();
		*pid = fork();
		if (*pid == 0)
			read_cmd(msh, fd, pid);
	}
	secure_close(&msh->fd_out, &msh->fd_in, &fd[0], &fd[1]);
	if (!msh->cmd_tab || !msh->cmd_tab[go_to_next_pipe(msh->cmd_tab)])
		return (NULL);
	return (&msh->cmd_tab[go_to_next_pipe(msh->cmd_tab) + 1]);
}

void	execute(t_minishell msh)
{
	int	num_of_child;

	msh.fd_in = 0;
	num_of_child = count_pipe(msh.lst.head);
	while (msh.cmd_tab && msh.cmd_tab[0])
		msh.cmd_tab = fork_and_execute(&msh, &msh.pid);
	if (msh.pid > 0)
		waitpid(msh.pid, &msh.last_status, 0);
	while (num_of_child-- > 0)
		wait(NULL);
	if (msh.pid == -1)
		return;
	if (WIFSIGNALED(msh.last_status))
	{
		if (msh.last_status == 2)
			set_or_get_exit_status(SET, 130);
		else if (msh.last_status == 131)
			set_or_get_exit_status(SET, 131);
		return;
	}
	msh.last_status = WEXITSTATUS(msh.last_status);
	set_or_get_exit_status(SET, msh.last_status);
}
