/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_and_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:50:13 by omougel           #+#    #+#             */
/*   Updated: 2024/06/28 17:44:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static char	**split_envp(t_ht_table *envp)
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

static char	**search_path(char **env, char **cmd, int in_child)
{
	size_t		i;
	char		*tmp;

	i = 0;
	while (env && env[i])
	{
		tmp = ft_strjoin_cmd(env[i], cmd[0]);
		if (!tmp)
			return (ft_free_split(env), NULL);
		if (check_executable_validity(tmp))
		{
			ft_free_split(env);
			if (in_child)
				return (replacefront(cmd, tmp));
			return (free(tmp), cmd);
		}
		free(tmp);
		i++;
	}
	ft_free_split(env);
	if (errno == 13)
		set_or_get_exit_status(SET, 126);
	else if (errno == 2)
		set_or_get_exit_status(SET, 127);
	return (ft_putstr_fd("mishell: executable command not found\n", 2), NULL);
}

char	**find_command(char **cmd, t_minishell *sh, int in_child)
{
	char	**env;

	if (is_builtin(cmd[0]))
		return (do_builtins(cmd, sh->env, sh), NULL);
	if (ft_strchr(cmd[0], '/') && !access(cmd[0], X_OK))
		return (cmd);
	env = split_envp(sh->env);
	return (search_path(env, cmd, in_child));
}

int	check_input(t_minishell *msh, char **input_redir, int fd_in)
{
	if (fd_in != 0)
		close(fd_in);
	if (!ft_strcmp(input_redir[0], "<"))
		fd_in = redir_input(input_redir[1]);
	else
		fd_in = here_doc(msh, input_redir[1], input_redir[2]);
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
