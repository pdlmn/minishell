/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:54:55 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/18 16:19:34 by emuminov         ###   ########.fr       */
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

void	inherit_props(t_token *t1, t_token *t2)
{
	t1->next = t2->next;
	t1->space_after = t2->space_after;
	if (t1->type != DELIM && t1->type != QDELIM)
		t1->type = WORD;
	if (t2->type == DELIM || t2->type == QDELIM)
		t1->type = t2->type;
	if (t2->next)
		t2->next->prev = t1;
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
	inherit_props(t1, t2);
	return (token_free(t2), t1);
}

t_tlist	*join_unspaced_words(t_tlist *lst, int is_in_heredoc)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if ((curr->type == WORD || curr->type == OTHER || curr->type == DELIM
				|| curr->type == QDELIM) && (!curr->space_after
				|| is_in_heredoc) && curr->next && (curr->next->type == WORD
				|| curr->next->type == OTHER || curr->next->type == DELIM
				|| curr->next->type == QDELIM))
		{
			curr = merge_word_tokens(curr, curr->next);
			if (!curr)
				return (NULL);
		}
		else
		{
			curr->is_quoted = NOT_QUOTED;
			curr = curr->next;
		}
	}
	return (lst);
}
