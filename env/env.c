/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:20:14 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/17 16:46:11 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"

t_ht_item	*env_row_to_ht_item(t_ht_table *ht, char *env_row)
{
	char		*env_row_c;
	char		*delimeter;
	t_ht_item	*res;

	env_row_c = ft_strdup(env_row);
	if (!env_row_c)
		return (NULL);
	delimeter = ft_strchr(env_row_c, '=');
	*delimeter = '\0';
	res = ht_set(ht, env_row_c, &env_row_c[delimeter - env_row_c + 1]);
	free(env_row_c);
	return (res);
}

t_ht_table	*env_arr_to_ht(char **env)
{
	int			i;
	t_ht_table	*ht;
	t_ht_item	*curr_item;

	ht = ht_new(100);
	if (!ht)
		return (NULL);
	i = 0;
	while (env[i])
	{
		curr_item = env_row_to_ht_item(ht, env[i++]);
		if (!curr_item)
			return (ht_free_table(ht), NULL);
	}
	return (ht);
}

t_ht_table	*env_increment_shlvl(t_ht_table *ht)
{
	char	*shlvl;
	int		int_shlvl;
	char	*new_shlvl;

	shlvl = ht_get(ht, "SHLVL");
	if (!shlvl)
	{
		new_shlvl = "1";
		if (!ht_set(ht, "SHLVL", new_shlvl))
			return (NULL);
		return (ht);
	}
	int_shlvl = ft_atoi(shlvl);
	new_shlvl = ft_itoa(int_shlvl + 1);
	if (!new_shlvl)
		return (NULL);
	if (!ht_set(ht, "SHLVL", new_shlvl))
		return (free(new_shlvl), NULL);
	return (free(new_shlvl), ht);
}

t_ht_table	*env_init(char **env, t_minishell *sh)
{
	sh->env = env_arr_to_ht(env);
	if (!sh->env)
		return (NULL);
	if (!env_increment_shlvl(sh->env))
		return (ht_free_table(sh->env), NULL);
	return (sh->env);
}

char	**env_ht_to_arr(t_ht_table *ht)
{
	char	**res;
	int		i;
	int		j;

	res = ft_calloc(ht->count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ht->size)
	{
		if (ht->items[i] && !ht->items[i]->is_deleted)
		{
			res[j] = ft_strjoin_delim(ht->items[i]->key, ht->items[i]->value,
					'=');
			if (!res[j++])
				return (ft_free_split(res), NULL);
		}
		i++;
	}
	return (res);
}
