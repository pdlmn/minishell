/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/08 19:28:26 by emuminov         ###   ########.fr       */
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

// char	*expand_variable(t_ht_table *ht, char *word)
// {
// 	char	**vars;
// 	char	*res;
// 	int		i;
//
// 	vars = ft_split(ft_strchr(word, '$'), '$');
// 	if (!vars)
// 		return (NULL);
// 	i = 0;
// 	while (vars[i])
// 	{
// 		if (ft_isdigit(vars[i][0]))
// 			vars[i] = expand_digit_variable(vars[i]);
// 		else
// 			vars[i] = expand_to_value(ht, vars[i]);
// 		if (!vars[i])
// 			return (ft_free_split(vars), NULL);
// 		i++;
// 	}
// 	res = join_expanded_variables(vars, word);
// 	return (ft_free_split(vars), res);
// }

// char	*expand_word(t_ht_table *ht, char *word)
// {
// 	char	*res;
// 	char	*tmp;
//
// 	if (word[0] == '\'' || word[0] == '"')
// 	{
// 		res = unquote(word, word[0]);
// 		if (!res)
// 			return (NULL);
// 	}
// 	else
// 		res = ft_strdup(word);
// 	if (word[0] == '\'')
// 		return (res);
// 	else
// 	{
// 		tmp = res;
// 		res = expand_variable(ht, res);
// 		if (!res)
// 			return (free(tmp), NULL);
// 		free(tmp);
// 	}
// 	return (res);
// }

// i
// "$ASD"$ASD
//      j

t_strlist	strlist_init()
{
	t_strlist	lst;

	lst.head = NULL;
	lst.tail = NULL;
	return (lst);
}

t_strnode	*strlist_append(t_strlist *lst, char *str)
{
	t_strnode	*node;

	node = ft_calloc(1, sizeof(t_strnode));
	node->str = str;
	node->len = ft_strlen(str);
	if (!node)
		return (NULL);
	if (!lst->head)
	{
		lst->head = node;
		lst->tail = node;
		return (node);
	}
	lst->tail->next = node;
	lst->tail = node;
	return (node);
}

// hel"lo$ASD"$ASD -> hello123123
// "lo$ASD" -> lo123

// char	*expand(char *s)
// {
// 	t_strlist	lst;
// 	char		*content_before_sigil;
// 	char		*sigil_var;
// 	char		*next_sigil_var;
// 	char		*key;
//
// 	lst = strlist_init();
// 	sigil_var = ft_strchr(s, '$');
// 	if (!sigil_var)
// 		return (ft_strdup(s));
// 	while (sigil_var)
// 	{
// 		content_before_sigil = ft_substr(s, 0, sigil_var - s);
// 		strlist_append(&lst, content_before_sigil);
// 		next_sigil_var = ft_strchr(sigil_var + 1, '$');
// 		if (next_sigil_var)
// 			key = ft_substr(sigil_var + 1, 0, next_sigil_var - sigil_var - 1);
// 		else
// 			key = ft_strdup(sigil_var + 1);
// 		
// 	}
// }

char	*get_key(char **sigil_var)
{
	const char	*next_sigil_var = ft_strchr(*sigil_var + 1, '$');
	char		*key;

	if (next_sigil_var)
		key = ft_substr(*sigil_var + 1, 0, next_sigil_var - *sigil_var - 1);
	else
		key = ft_strdup(*sigil_var + 1);
	*sigil_var = (char *)next_sigil_var;
	if (!key)
		return (NULL);
	return (key);
}

char	*expand_key(t_ht_table *ht, char *key, char *str_before_sigil)
{
	char	*expanded_var;
	char	*res;

	expanded_var = ht_get(ht, key);
	if (expanded_var)
	{
		res = ft_strjoin(str_before_sigil, expanded_var);
		return (res);
	}
	return (ft_strdup(str_before_sigil));
}

char	*expand_keys(t_ht_table *ht, char *s, char *sigil)
{
	char	*key;
	char	*res;
	char	*tmp;

	res = ft_substr(s, 0, sigil - s);
	if (!res)
		return (NULL);
	while (sigil)
	{
		key = get_key(&sigil);
		if (!key)
			return (free(s), free(res), NULL);
		tmp = res;
		res = expand_key(ht, key, res);
		if (!res)
			return (free(s), free(res), free(key), NULL);
		free(key);
		free(tmp);
	}
	return (res);
}

char	*expand_dquoted(t_ht_table *ht, const char *s)
{
	char	*quotes_content;
	char	*sigil;
	char	*res;

	quotes_content = ft_substr(s, 1, ft_strchr(s + 1, s[0]) - s - 1);
	if (!quotes_content)
		return (NULL);
	sigil = ft_strchr(quotes_content, '$');
	if (!sigil)
		return (quotes_content);
	res = expand_keys(ht, quotes_content, sigil);
	if (!res)
		return (free(quotes_content), NULL);
	return (free(quotes_content), res);
}

// expand_word
// while word[i]
//   if word[i] == ' || word[i] == "
//     add_quotes_content_to_strlist(&word[i])
//   else if (ft_isalpha(word[i]))
//     add_word_to_strlist(&word[i])

// char	***expansion(t_ht_table *ht, char ***cmd_tab)
// {
// 	char	*expanded;
// 	int		i;
// 	int		j;
//
// 	i = 0;
// 	while (cmd_tab[i])
// 	{
// 		j = 0;
// 		while (cmd_tab[j])
// 		{
// 			if (ft_strchr(cmd_tab[i][j], '$'))
// 			{
// 				expanded = expand_word(ht, cmd_tab[i][j]);
// 				free(cmd_tab[i][j]);
// 				cmd_tab[i][j] = expanded;
// 				if (!cmd_tab[i][j])
// 					return (ft_free_table(cmd_tab), NULL);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (cmd_tab);
// }
