/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:47:00 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 00:51:38 by omougel          ###   ########.fr       */
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
	return (last);
}

int	prev(char **newpwd)
{
	if (last_occ(*newpwd, '/') != 0)
		*newpwd[last_occ(*newpwd, '/')] = '\0';
	return(2);
}

int next(char *path, char **newpwd)
{
	char *tmp;
	int	i;
	int	t;

	i = 0;
	tmp = malloc(ft_strlen(*newpwd) + ft_strlen_till_c(path, '/') + 2);
	ft_strlcpy(tmp, *newpwd, ft_strlen(*newpwd));
	t = ft_strlen(tmp);
	tmp[t++] = '/';
	while (path[i] && path[i] != '/')
		tmp[t++] = path[i++];
	tmp[t] = '\0';
	free(*newpwd);
	*newpwd = tmp;
	return (i);
}

char  *find_newpwd(char *path, t_ht_table *env)
{
	char  *newpwd;
	int	  i;

	i = 0;
	if (path[0] == '/')
		return (path);
	newpwd = ht_get(env, "PWD");
	while (path[i])
	{
		if (path[i] == '/')
			i++;
		else if (!ft_strncmp(&path[i], "../", 3) || !ft_strncmp(&path[i], "..", 2))
			i += prev(&newpwd);
		else
			i += next(&path[i], &newpwd);
	}
	return (newpwd);
}

int	cd(char **cmd, t_ht_table *env)
{
	char  *newpwd;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
		return (ft_putstr_fd("mishell: cd: invalid option\n", 2), 2);
	if (cmd[2])
		return (ft_putstr_fd("mishell: cd: too many arguments\n", 2), 1);
	if (!ft_strcmp(cmd[1], "-"))
	{
		newpwd = ht_get(env, "OLDPWD");
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
	return (0);
}
