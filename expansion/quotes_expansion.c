/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:56:44 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/17 18:35:58 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static t_token	*join_quotes_content(t_token *quote_token)
{
	t_token	*curr;

	curr = quote_token->next;
	while (curr)
	{
		if (curr->is_quoted == END_QUOTE)
			return (curr);
		else if ((curr->type == WORD || curr->type == OTHER) && curr->next
			&& (curr->next->type == WORD || curr->next->type == OTHER))
		{
			curr = merge_word_tokens(curr, curr->next);
			if (!curr)
				return (NULL);
		}
		else
			curr = curr->next;
	}
	return (quote_token->next);
}

t_tlist	*expand_quotes(t_tlist *lst)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->is_quoted == START_QUOTE)
		{
			curr = join_quotes_content(curr);
			if (!curr)
				return (NULL);
		}
		curr = curr->next;
	}
	return (lst);
}

t_tlist	*remove_quotes(t_tlist *lst)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if ((curr->type == SQUOTE || curr->type == DQUOTE) && (curr->next
				|| curr->prev))
		{
			curr = token_delete_and_free(lst, curr);
			continue ;
		}
		if ((curr->type == SQUOTE || curr->type == DQUOTE) && !curr->next
			&& !curr->prev)
			token_convert_to_empty_word(curr);
		curr = curr->next;
	}
	return (lst);
}
