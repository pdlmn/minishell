/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/04 12:48:39 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

char	*expand_to_value(t_ht_table *ht, char *var)
{
	char	*expanded;
	char	*val;

	val = ht_get(ht, var);
	if (!val)
	{
		var[0] = '\0';
		return (var);
	}
	expanded = ft_strdup(val);
	if (!expanded)
		return (NULL);
	return (free(var), expanded);
}

char	*expand_variable(t_ht_table *ht, char *word)
{
	char	**vars;
	char	*res;
	int		i;

	vars = ft_split(ft_strchr(word, '$'), '$');
	if (!vars)
		return (NULL);
	i = 0;
	while (vars[i])
	{
		if (ft_isdigit(vars[i][0]))
			vars[i] = expand_digit_variable(vars[i]);
		else
			vars[i] = expand_to_value(ht, vars[i]);
		if (!vars[i])
			return (ft_free_split(vars), NULL);
		i++;
	}
	res = join_expanded_variables(vars, word);
	return (ft_free_split(vars), res);
}

char	*expand_word(t_ht_table *ht, char *word)
{
	char	*res;
	char	*tmp;

	if (word[0] == '\'' || word[0] == '"')
	{
		res = unquote(word, word[0]);
		if (!res)
			return (NULL);
	}
	else
		res = ft_strdup(word);
	if (word[0] == '\'')
		return (res);
	else
	{
		tmp = res;
		res = expand_variable(ht, res);
		if (!res)
			return (free(tmp), NULL);
		free(tmp);
	}
	return (res);
}

char	***expansion(t_ht_table *ht, char ***cmd_tab)
{
	char	*expanded;
	int		i;
	int		j;

	i = 0;
	while (cmd_tab[i])
	{
		j = 0;
		while (cmd_tab[j])
		{
			if (ft_strchr(cmd_tab[i][j], '$'))
			{
				expanded = expand_word(ht, cmd_tab[i][j]);
				free(cmd_tab[i][j]);
				cmd_tab[i][j] = expanded;
				if (!cmd_tab[i][j])
					return (ft_free_table(cmd_tab), NULL);
			}
			j++;
		}
		i++;
	}
	return (cmd_tab);
}
