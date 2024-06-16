/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:54:42 by omougel           #+#    #+#             */
/*   Updated: 2024/06/16 23:56:39 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

static char	*strvalue(char *envval, char *cmd)
{
	char	*newval;

	newval = &cmd[valuelen(cmd)];
	if (cmd[keylen(cmd)] == '+' && cmd[keylen(cmd) + 1] != '=')
	{
		ft_putstr_fd("mishell: export: not a valid indentifier\n", 2);
		return (set_or_get_exit_status(SET, 1), NULL);
	}
	if (cmd[keylen(cmd)] != '+' || !envval)
		return (ft_strdup(newval));
	return (ft_strjoin(envval, newval));
}

static int is_correct_variable_name(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("mishell: export: not a valid indentifier\n", 2);
		return (set_or_get_exit_status(SET, 1));
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("mishell: export: not a valid indentifier\n", 2);
			return (set_or_get_exit_status(SET, 1));
		}
		i++;
	}
	return (0);
}

static void	export(char **cmd, t_ht_table *env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
		return (set_or_get_exit_status(SET, 2),
			ft_putstr_fd("mishell: export: invalid option\n", 2));
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[1], '='))
			continue ;
		key = ft_substr(cmd[i], 0, keylen(cmd[i]));
		if (is_correct_variable_name(key))
			return ;
		value = strvalue(ht_get(env, key), cmd[i]);
		if (!value || !key)
			return (set_or_get_exit_status(SET, -1), free(key), free(value));
		if (!ht_set(env, key, value))
			return (set_or_get_exit_status(SET, -1), free(key), free(value));
		free(key);
		free(value);
	}
	set_or_get_exit_status(SET, 0);
}

static void	unset(char **cmd, t_ht_table *env)
{
	int	i;

	i = 1;
	if (cmd[1] && cmd[1][0] == '-')
		return (set_or_get_exit_status(SET, 2),
			ft_putstr_fd("mishell: unset: invalid option\n", 2));
	while (cmd[i])
		ht_delete(env, cmd[i++]);
	set_or_get_exit_status(SET, 0);
}

void	do_builtins(char **cmd, t_ht_table *env, t_minishell *sh)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (echo(cmd, sh->fd_out));
	if (!ft_strcmp(cmd[0], "cd"))
		return (cd(cmd, env));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (pwd(cmd, sh, sh->fd_out));
	if (!ft_strcmp(cmd[0], "export"))
		return (export(cmd, env));
	if (!ft_strcmp(cmd[0], "unset"))
		return (unset(cmd, env));
	if (!ft_strcmp(cmd[0], "env"))
		return (bt_env(cmd, env, sh->fd_out));
	if (!ft_strcmp(cmd[0], "exit"))
		return (bt_exit(cmd, sh));
}
