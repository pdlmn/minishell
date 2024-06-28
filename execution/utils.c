/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:06:42 by omougel           #+#    #+#             */
/*   Updated: 2024/06/28 16:37:55 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	export_error(char *key, char *value, t_ht_table *env)
{
	if (!value)
		return (free(key), set_or_get_exit_status(SET, -1));
	if (!ht_set(env, key, value))
		return (free(key), free(value), set_or_get_exit_status(SET, -1));
	return (0);
}

void	err_msg(t_minishell *msh)
{
	ft_putstr_fd("mishell: exit: numeric argument required\n", 2);
	errno = 2;
	ft_exit(msh);
}

int	read_path(int i, char *path, char *newpwd)
{
	if (path[i] == '/')
		i++;
	else if (!ft_strncmp(&path[i], "..", 2))
		i += prev(newpwd);
	else if (path[i] == '.')
		i++;
	else
		i += next(&path[i], newpwd);
	return (i);
}

int	set_oldpwd(char *newpwd, t_ht_table *env)
{
	ft_strcpy(newpwd, ht_get(env, "OLDPWD"));
	if (!newpwd[0])
		return (ft_putstr_fd("mishell: cd: OLDPWD not set\n", 2), 2);
	printf("%s\n", newpwd);
	return (0);
}

void  go_to_home(t_ht_table *env, char *newpwd)
{
	ft_strcpy(newpwd, ht_get(env, "HOME"));
	if (!newpwd[0])
		return (set_or_get_exit_status(SET, 1),
			ft_putstr_fd("mishell: cd: HOME not set\n", 2));
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
