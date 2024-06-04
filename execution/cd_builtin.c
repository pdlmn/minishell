/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:47:00 by omougel           #+#    #+#             */
/*   Updated: 2024/06/04 19:43:40 by emuminov         ###   ########.fr       */
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

char	*find_newpwd(char *path, t_minishell *sh)
{
	char	*newpwd;
	int		i;

	i = 0;
	if (path[0] == '/')
		return (ft_strdup(path));
	newpwd = ft_strdup(ht_get(sh->env, "PWD"));
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
			i += prev(&newpwd);
		else if (path[i] == '.')
			i++;
		else
			i += next(&path[i], &newpwd);
	}
	return (newpwd);
}

int	cd(char **cmd, t_minishell *sh)
{
	char			*newpwd;
	struct	stat	buf;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
		return (ft_putstr_fd("mishell: cd: invalid option\n", 2), 2);
	if (cmd[2])
		return (ft_putstr_fd("mishell: cd: too many arguments\n", 2), 1);
	stat(cmd[1], &buf);
	if (!ft_strcmp(cmd[1], "-"))
	{
		newpwd = ht_get(sh->env, "OLDPWD");
		if (!newpwd)
			return (ft_putstr_fd("mishell: cd: OLDPWD not set\n", 2), 1);
		newpwd = ft_strdup(newpwd);
	}
	else if (!S_ISDIR(buf.st_mode))
		return (ft_putstr_fd("mishell: cd: not a dir\n", 2), 1);
	else if (cmd[1] && !access(cmd[1], F_OK))
		newpwd = find_newpwd(cmd[1], sh);
	else
		return (ft_putstr_fd("mishell: cd: No such file or directory\n", 2), 1);
	if (!newpwd)
		return (ft_putstr_fd("mishell: cd: OLDPWD not set\n", 2), 1);
	ht_set(sh->env, "OLDPWD", ht_get(sh->env, "PWD"));
	ht_set(sh->env, "PWD", newpwd);
	chdir(newpwd);
	free(newpwd);
	return (0);
}
