/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:54:42 by omougel           #+#    #+#             */
/*   Updated: 2024/06/10 09:23:53 by omougel          ###   ########.fr       */
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

char	*strvalue(char *envval, char *cmd)
{
	char	*newval;

	newval = &cmd[valuelen(cmd)];
	if (!cmd[keylen(cmd)] || !newval)
		return (ft_strdup(newval));
	return (ft_strjoin(envval, newval));
}

int	call_env(t_ht_table *env, int fd_out)
{
	char	**str;
	int		i;

	str = ft_calloc(2, sizeof(char *));
	str[0] = "env";
	i = bt_env(str, env, fd_out);
	free(str);
	return (i);
}

int	export(char **cmd, t_ht_table *env, int fd_out)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (!cmd[1])
		call_env(env, fd_out);
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: export: invalid option\n", 2), 2);
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[1], '='))
			continue ;
		key = ft_substr(cmd[i], 0, keylen(cmd[i]));
		value = strvalue(ht_get(env, key), cmd[i]);
		ht_set(env, key, value);
	}
	free(key);
	free(value);
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
		return (cd(cmd, sh));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (pwd(cmd, sh, sh->fd_out));
	if (!ft_strcmp(cmd[0], "export"))
		return (export(cmd, env, sh->fd_out));
	if (!ft_strcmp(cmd[0], "unset"))
		return (unset(cmd, env));
	if (!ft_strcmp(cmd[0], "env"))
		return (bt_env(cmd, env, sh->fd_out));
	if (!ft_strcmp(cmd[0], "exit"))
		bt_exit(sh);
	return (1);
}
