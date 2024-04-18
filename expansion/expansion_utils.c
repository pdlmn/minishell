/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:54:55 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/17 19:08:18 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

t_token	*token_convert_to_word(t_token *t)
{
	t->type = WORD;
	t->op_type = NOT_OPERATOR;
	if (t->is_quoted == START_QUOTE || t->is_quoted == END_QUOTE)
		t->is_quoted = NOT_QUOTED;
	return (t);
}

t_token	*token_convert_to_empty_word(t_token *t)
{
	token_convert_to_word(t);
	t->content[0] = '\0';
	t->len = 0;
	return (t);
}

t_token	*merge_word_tokens(t_token *t1, t_token *t2)
{
	char	*s;
	int		len;

	len = t1->len + t2->len;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, t1->content, sizeof(char) * t1->len);
	ft_memcpy(&s[t1->len], t2->content, sizeof(char) * t2->len);
	s[len] = '\0';
	free(t1->content);
	t1->content = s;
	t1->len = len;
	t1->next = t2->next;
	t1->type = WORD;
	if (t2->next)
		t2->next->prev = t1;
	return (token_free(t2), t1);
}

t_tlist	*join_unspaced_words(t_tlist *lst)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if ((curr->type == WORD || curr->type == OTHER)
			&& !curr->space_after && curr->next
			&& (curr->next->type == WORD || curr->next->type == OTHER))
		{
			curr = merge_word_tokens(curr, curr->next);
			if (!curr)
				return (NULL);
		}
		else
			curr = curr->next;
	}
	return (lst);
}