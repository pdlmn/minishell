/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/03 02:23:42 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

int	srtrlen_excluding_symbol(char *str, int c)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (str[i])
	{
		if (str[i] != c)
			l++;
		i++;
	}
	return (l);
}

char	*unquote(char *word, int quote)
{
	const int	l = srtrlen_excluding_symbol(word, quote);
	char		*res;
	int			i;
	int			j;

	res = malloc(sizeof(char) * (l + 1));
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] != quote)
		{
			res[j] = word[i];
			j++;
		}
		i++;
	}
	return (res);
}

char	*join_expanded_variables(char **vars, char *word)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_substr(word, 0, ft_strchr(word, '$') - word);
	if (!res)
		return (ft_free_split(vars), NULL);
	while (vars[i])
	{
		tmp = ft_strjoin(res, vars[i]);
		if (!tmp)
			return (ft_free_split(vars), free(res), NULL);
		free(res);
		res = tmp;
		i++;
	}
	return (res);
}

char	*expand_digit_variable(char **vars, int i)
{
	char	*expanded;

	expanded = ft_strdup(&vars[i][1]);
	if (!expanded)
		return (ft_free_split(vars), NULL);
	return (free(vars[i]), expanded);
}

char	*expand_to_value(char **vars, char *val, int i)
{
	char	*expanded;

	expanded = ft_strdup(val);
	if (!expanded)
		return (ft_free_split(vars), NULL);
	return (free(vars[i]), expanded);
}

char	*expand_variable(t_ht_table *ht, char *word)
{
	char	**vars;
	char	*val;
	int		i;

	vars = ft_split(ft_strchr(word, '$'), '$');
	if (!vars)
		return (NULL);
	i = 0;
	while (vars[i])
	{
		if (ft_isdigit(vars[i][0]))
			vars[i] = expand_digit_variable(vars, i);
		else
		{
			val = ht_get(ht, vars[i]);
			if (!val)
				vars[i][0] = '\0';
			else
				vars[i] = expand_to_value(vars, val, i);
		}
		i++;
	}
	return (join_expanded_variables(vars, word));
}

char	*expand_word(t_ht_table *ht, char *word)
{
	char	*res;
	char	*tmp;

	res = NULL;
	if (word[0] == '\'' || word[0] == '"')
	{
		res = unquote(word, word[0]);
		if (!res)
			return (NULL);
	}
	if (word[0] == '\'')
		return (res);
	else if (word[0] == '"')
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
	int	i;
	int	j;

	i = 0;
	while (cmd_tab[i])
	{
		j = 0;
		while (cmd_tab[j])
		{
			if (ft_strchr(cmd_tab[i][j], '$'))
			{
				free(cmd_tab[i][j]);
				cmd_tab[i][j] = expand_word(ht, cmd_tab[i][j]);
				if (!cmd_tab[i][j])
				{
					ft_free_table(cmd_tab);
					return (NULL);
				}
			}
			j++;
		}
		i++;
	}
	return (cmd_tab);
}
