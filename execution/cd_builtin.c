/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:47:00 by omougel           #+#    #+#             */
/*   Updated: 2024/06/18 13:38:06 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static int	last_occ(char *str, char c)
{
	int	i;
	int	last;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			last = i;
		i++;
	}
	if (last == 0)
		return (1);
	return (last);
}

static int	prev(char *newpwd)
{
	if (last_occ(newpwd, '/') != 1 || newpwd[1] != '\0')
		newpwd[last_occ(newpwd, '/')] = '\0';
	return (2);
}

static int	next(char *path, char *newpwd)
{
	int	pathlen;
	int	newpwdlen;

	newpwdlen = ft_strlen(newpwd);
	newpwd[newpwdlen++] = '/';
	newpwd[newpwdlen] = '\0';
	pathlen = ft_strlen_till_c(path, '/') + ft_strlen(newpwd) + 1;
	ft_strlcat(newpwd, path, pathlen);
	return (ft_strlen_till_c(path, '/'));
}

static char	*find_newpwd(char *path, char *newpwd, t_ht_table *env)
{
	int		i;

	i = 0;
	if (path[0] == '/')
		return (ft_strcpy(newpwd, path));
	getcwd(newpwd, PATH_MAX);
	if (!newpwd[0] && ht_get(env, "PWD"))
		ft_strcpy(newpwd, ht_get(env, "PWD"));
	else if (!newpwd[0] && !ht_get(env, "PWD"))
		return (ft_putstr_fd("mishell: pwd: no such file or directory\n", 2),
				set_or_get_exit_status(SET, 1), NULL);
	if (!ht_set(env, "PWD", newpwd))
		return (set_or_get_exit_status(SET, -1), NULL);
	while (path[i])
	{
		if (!ft_strncmp(&path[i], "...", 3))
			return (NULL);
		if (path[i] == '/')
			i++;
		else if (!ft_strncmp(&path[i], "..", 2))
			i += prev(newpwd);
		else if (path[i] == '.')
			i++;
		else
			i += next(&path[i], newpwd);
	}
	return (newpwd);
}

void	cd(char **cmd, t_ht_table *env)
{
	char		newpwd[PATH_MAX];

	set_or_get_exit_status(SET, 2);
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
		return (ft_putstr_fd("mishell: cd: invalid option\n", 2));
	if (cmd[1] && cmd[2])
		return (ft_putstr_fd("mishell: cd: too many arguments\n", 2));
	if (ft_strcmp(cmd[1], "-") == 0)
	{
		ft_strcpy(newpwd, ht_get(env, "OLDPWD"));
		if (!newpwd[0])
			return (ft_putstr_fd("mishell: cd: OLDPWD not set\n", 2));
	}
	else if (cmd[1])
		if (!find_newpwd(cmd[1], newpwd, env))
			return ;
	if (chdir(newpwd) != 0)
		return (set_or_get_exit_status(SET, 1), perror("minishell: cd"));
	if (!ht_set(env, "OLDPWD", ht_get(env, "PWD"))
		|| !ht_set(env, "PWD", newpwd))
	{
		set_or_get_exit_status(SET, -1);
		return ;
	}
	set_or_get_exit_status(SET, 0);
}
