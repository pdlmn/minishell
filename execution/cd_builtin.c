/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:47:00 by omougel           #+#    #+#             */
/*   Updated: 2024/06/03 00:23:20 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	last_occ(char *str, char c)
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

int	prev(char **newpwd)
{
	char *tmp;

	if (last_occ(*newpwd, '/') != 1 || newpwd[0][1] != '\0')
	{
		tmp = ft_substr(*newpwd, 0, last_occ(*newpwd, '/'));
		free(*newpwd);
		*newpwd	= tmp;
	}
	return (2);
}

int	next(char *path, char **newpwd)
{
	char	*tmp;
	int		i;
	int		t;

	i = 0;
	tmp = malloc(ft_strlen(*newpwd) + ft_strlen_till_c(path, '/') + 2);
	ft_strcpy(tmp, *newpwd);
	t = ft_strlen(tmp);
	if (tmp[t - 1] != '/')
		tmp[t++] = '/';
	while (path[i] && path[i] != '/')
		tmp[t++] = path[i++];
	tmp[t] = '\0';
	free(*newpwd);
	*newpwd = tmp;
	return (i);
}

char	*find_newpwd(char *path, t_ht_table *env)
{
	char	*newpwd;
	int		i;

	i = 0;
	if (path[0] == '/')
		return (path);
	newpwd = ft_strdup(ht_get(env, "PWD"));
	while (path[i])
	{
		if (path[i] == '/')
			i++;
		else if (!ft_strncmp(&path[i], "..", 2))
			i += prev(&newpwd);
		else if (path[i] == '.')
			i++;
		else
			i += next(&path[i], &newpwd);
	}
	return (newpwd);
}

int	cd(char **cmd, t_ht_table *env)
{
	char	*newpwd;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
		return (ft_putstr_fd("mishell: cd: invalid option\n", 2), 2);
	if (cmd[2])
		return (ft_putstr_fd("mishell: cd: too many arguments\n", 2), 1);
	if (!ft_strcmp(cmd[1], "-"))
	{
		newpwd = ft_strdup(ht_get(env, "OLDPWD"));
		if (!newpwd)
			return (ft_putstr_fd("mishell: cd: OLDPWD not set\n", 2), 1);
	}
	else if (cmd[1] && !access(cmd[1], F_OK))
		newpwd = find_newpwd(cmd[1], env);
	else
		return (ft_putstr_fd("mishell: cd: No such file or directory\n", 2), 1);
	ht_set(env, "OLDPWD", ht_get(env, "PWD"));
	ht_set(env, "PWD", newpwd);
	chdir(newpwd);
	free(newpwd);
	return (0);
}
