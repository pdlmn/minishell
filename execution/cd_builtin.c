/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:47:00 by omougel           #+#    #+#             */
/*   Updated: 2024/06/10 09:30:09 by omougel          ###   ########.fr       */
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

int	prev(char *newpwd)
{
	if (last_occ(newpwd, '/') != 1 || newpwd[1] != '\0')
		newpwd[last_occ(newpwd, '/')] = '\0';
	return (2);
}

int	next(char *path, char *newpwd)
{
	int	len;

	newpwd[ft_strlen(newpwd)] = '/';
	len = ft_strlen_till_c(path, '/') + ft_strlen(newpwd) + 1;
	ft_strlcat(newpwd, path, len);
	return (ft_strlen_till_c(path, '/'));
}

char	*find_newpwd(char *path, t_minishell *sh, char *newpwd)
{
	int	i;

	i = 0;
	if (path[0] == '/')
		return (ft_strcpy(newpwd, path));
	ft_strcpy(newpwd, ht_get(sh->env, "PWD"));
	if (!newpwd)
	{
		newpwd = getcwd(NULL, 0);
		if (!newpwd)
			ft_exit(sh);
		ht_set(sh->env, "PWD", newpwd);
	}
	while (path[i])
	{
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

int	cd(char **cmd, t_minishell *sh)
{
	char		newpwd[PATH_MAX];
	struct stat	buf;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
		return (ft_putstr_fd("mishell: cd: invalid option\n", 2), 2);
	if (cmd[1] && cmd[2])
		return (ft_putstr_fd("mishell: cd: too many arguments\n", 2), 1);
	stat(cmd[1], &buf);
	if (!ft_strcmp(cmd[1], "-"))
	{
		ft_strcpy(newpwd, ht_get(sh->env, "OLDPWD"));
		if (!newpwd[0])
			return (ft_putstr_fd("mishell: cd: OLDPWD not set\n", 2), 1);
	}
	else if (cmd[1])
		find_newpwd(cmd[1], sh, newpwd);
	if (chdir(newpwd) != 0)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		return (1);
	}
	ht_set(sh->env, "OLDPWD", ht_get(sh->env, "PWD"));
	ht_set(sh->env, "PWD", newpwd);
	return (0);
}
