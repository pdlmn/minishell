/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_unspaced.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:44:57 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 16:45:49 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static t_token	*split_spaced_token(t_token *token)
{
	char	**words;
	int		i;
	t_tlist	tmp_lst;
	t_token	*new_token;

	tmp_lst.head = NULL;
	tmp_lst.tail = NULL;
	words = ft_split(token->content, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		new_token = token_create(words[i], ft_strlen(words[i]), 1, NOT_QUOTED);
		if (!new_token)
			return (token_list_free(&tmp_lst), NULL);
		token_list_append(&tmp_lst, new_token);
		i++;
	}
	free(words);
	return (tmp_lst.head);
}

t_tlist	*split_spaced_unqouted_tokens(t_tlist *lst)
{
	t_token	*curr;
	t_token	*next;
	t_token	*first_new_token;

	curr = lst->head;
	while (curr)
	{
		if ((curr->is_quoted == NOT_QUOTED) && ft_strchr(curr->content, ' '))
		{
			first_new_token = split_spaced_token(curr);
			if (!first_new_token)
				return (NULL);
			next = curr->next;
			token_insert_tokens(lst, curr, first_new_token);
			token_free(curr);
			curr = next;
			continue ;
		}
		curr = curr->next;
	}
	return (lst);
}
