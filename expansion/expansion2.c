/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:48:19 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/04 12:48:38 by emuminov         ###   ########.fr       */
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
		if (str[i++] != c)
			l++;
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
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] != quote)
			res[j++] = word[i];
		i++;
	}
	res[l] = '\0';
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

char	*expand_digit_variable(char *var)
{
	char	*expanded;

	expanded = ft_strdup(&var[1]);
	if (!expanded)
		return (NULL);
	return (free(var), expanded);
}
