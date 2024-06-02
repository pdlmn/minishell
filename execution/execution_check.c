/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:13:31 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 00:14:35 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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
