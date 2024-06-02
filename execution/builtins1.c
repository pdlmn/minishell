/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:54:42 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 22:23:53 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

size_t	keylen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=' && str[i] != '+' && str[i])
		i++;
	return (i);
}

size_t	valuelen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (i);
	return (i + 1);
}

char  *strvalue(char *envval, char *newval, char plus)
{
	if (!plus || !envval)
		return (newval);
	return (ft_strjoin(envval, newval));
}

int	export(char **cmd, t_ht_table *env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: export: invalid option\n", 2), 2);
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[1], '='))
			continue ;
		key = ft_substr(cmd[i], 0, keylen(cmd[i]));
		value = strvalue(ht_get(env, key), &cmd[i][valuelen(cmd[i])], cmd[i][keylen(cmd[i])]);
		ht_set(env, key, value);
	}
	return (0);
}

int	unset(char **cmd, t_ht_table *env)
{
	int	i;

	i = 1;
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: unset: invalid option\n", 2), 2);
	while (cmd[i])
		ht_delete(env, cmd[i++]);
	return (0);
}

int	do_builtins(char **cmd, t_ht_table *env, t_minishell *sh)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (echo(cmd, sh->fd_out));
	if (!ft_strcmp(cmd[0], "cd"))
		return (cd(cmd, env));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (pwd(cmd, env, sh->fd_out));
	if (!ft_strcmp(cmd[0], "export"))
		return (export(cmd, env));
	if (!ft_strcmp(cmd[0], "unset"))
		return (unset(cmd, env));
	if (!ft_strcmp(cmd[0], "env"))
		return (bt_env(cmd, env, sh->fd_out));
	if (!ft_strcmp(cmd[0], "exit"))
		bt_exit(sh);
	return (1);
}
