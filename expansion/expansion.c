/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/02 21:28:25 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

// expand_word
//   

// char *expand_word(t_ht_table *ht, char *word)
// {
// 	
// 	return (NULL);
// }

char	*expand_word(t_ht_table *ht, char *word)
{
	char	**vars;
	char	*val;
	char	*expanded;
	char	*res;
	char	*tmp;
	int		i;

	vars = ft_split(ft_strchr(word, '$'), '$');
	if (!vars)
		return (NULL);
	i = 0;
	while (vars[i])
	{
		if (ft_isdigit(vars[i][0]))
		{
			expanded = ft_strdup(&vars[i][1]);
			if (!expanded)
			{
				ft_free_split(vars);
				return (NULL);
			}
			free(vars[i]);
			vars[i] = expanded;
		}
		val = ht_get(ht, vars[i]);
		if (!val)
		{
			vars[i][0] = '\0';
		}
		else
		{
			expanded = ft_strdup(val);
			if (!expanded)
			{
				ft_free_split(vars);
				return (NULL);
			}
			free(vars[i]);
			vars[i] = expanded;
		}
		i++;
	}
	i = 0;
	res = ft_substr(word, 0, ft_strchr(word, '$') - word);
	if (!res)
	{
		ft_free_split(vars);
		return (NULL);
	}
	while (vars[i])
	{
		tmp = ft_strjoin(res, vars[i]);
		if (!tmp)
		{
			ft_free_split(vars);
			free(res);
			return (NULL);
		}
		free(res);
		res = tmp;
		i++;
	}
	return (res);
}

// Variable names can contain uppercase, lowercase letters, numbers, underscores, and digits.
// They can't start with digits.
char	***expansion(t_ht_table *ht, char ***cmd_tab)
{
	// while i
	//   while j
	//     while c
	//       if c == '$' && check_if_valid_variable(&c)
	//         expand(ht, cmd_tab[j])

}
