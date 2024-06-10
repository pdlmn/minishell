/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_and_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:50:13 by omougel           #+#    #+#             */
/*   Updated: 2024/06/10 10:49:41 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

char	**split_envp(t_ht_table *envp)
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

char	**seach_path(char **env, char **cmd)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (env && env[i])
	{
		tmp = ft_strjoin_cmd(env[i], cmd[0]);
		if (!tmp)
			return (NULL);
		if (!access(tmp, X_OK))
		{
			ft_free_split(env);
			return (replacefront(cmd, tmp));
		}
		free(tmp);
		i++;
	}
	ft_free_split(env);
	errno = 127;
	ft_putstr_fd(cmd[0], 2);
	return (ft_putstr_fd(": command not found\n", 2), NULL);
}

char	**find_command(char **cmd, t_minishell *sh)
{
	char	**env;

	if (is_builtin(cmd[0]))
	{
		sh->last_status = do_builtins(cmd, sh->env, sh);
		return (NULL);
	}
	if (!ft_strncmp("./", cmd[0], 2) && !access(cmd[0], X_OK))
		return (cmd);
	env = split_envp(sh->env);
	return (seach_path(env, cmd));
}

int	check_input(char **input_redir, int fd_in)
{
	if (fd_in != 0)
		close(fd_in);
	if (!ft_strcmp(input_redir[0], "<"))
		fd_in = redir_input(input_redir[1]);
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
