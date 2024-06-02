/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_and_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:50:13 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 01:51:32 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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
