/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/10 20:17:38 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

/* 1. Replace non singly-quoted $ values.
 * 2. Join all strings.
 * 3. Remove empty quotes.
 * 4.
 * 5. */

t_token	*token_find_prev(t_token *lst, t_token *t)
{
	t_token	*curr;
	t_token	*prev;

	curr = lst;
	prev = NULL;
	while (curr)
	{
		if (curr == t)
			return (prev);
		prev = curr;
		curr = curr->next;
	}
	return (prev);
}

t_token	*expand_sigil(t_ht_table *ht, t_token **lst, t_token *sigil_token)
{
	t_token	*prev;
	char	*val;
	char	*copied_val;
	t_token	*res;

	if (!sigil_token->space_after && sigil_token->next
		&& sigil_token->next->op_type == NOT_OPERATOR)
	{
		prev = token_find_prev(*lst, sigil_token);
		if (sigil_token->next->type == WORD)
		{
			// delete SIGIL, replace contents of the next word with cloned ht value
			val = ht_get(ht, sigil_token->next->content);
			copied_val = ft_strdup(val);
			if (!copied_val)
				return (NULL);
			free(sigil_token->next->content);
			sigil_token->next->content = copied_val;
			sigil_token->next->len = ft_strlen(copied_val);
			if (prev)
				prev->next = sigil_token->next;
			else
				*lst = sigil_token->next;
			res = sigil_token->next;
			token_free(sigil_token);
			return (res);
		}
		else if ((sigil_token->next->type == QUOTE || sigil_token->next->type == DQUOTE)
				&& sigil_token->is_quoted == NOT_QUOTED)
		{
			// delete SIGIL
			if (prev)
				prev->next = sigil_token->next;
			else
				*lst = sigil_token->next;
			res = sigil_token->next;
			token_free(sigil_token);
			return (res);
		}
		else if (sigil_token->next->type == DQUOTE && sigil_token->is_quoted == DQUOTED)
		{
			// convert SIGIL to word
			sigil_token->type = WORD;
			sigil_token->space_after = 0;
			return (sigil_token);
		}
	}
	else if (sigil_token->space_after || !sigil_token->next)
	{
		// convert SIGIL to word
		sigil_token->type = WORD;
		sigil_token->space_after = 0;
		return (sigil_token);
	}
	return (sigil_token);
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
	s[t2->len] = '\0';
	free(t1->content);
	t1->content = s;
	t1->len = len;
	t1->next = t2->next;
	return (token_free(t2), t1);
}

t_token	*join_quotes_content(t_token *quote_token)
{
	t_token	*curr;

	curr = quote_token->next;
	while (curr)
	{
		if (curr->is_quoted == END_QUOTE)
			return (curr->next);
		else if (curr->type == WORD && curr->next && curr->next->type == WORD)
		{
			curr = merge_word_tokens(curr, curr->next);
			if (!curr)
				return (NULL);
		}
		else
			curr = curr->next;
	}
	return (curr);
}

t_token	*expand_sigils(t_ht_table *ht, t_token **lst)
{
	t_token	*curr;

	curr = *lst;
	while (curr)
	{
		if (curr->type == SIGIL)
		{
			curr = expand_sigil(ht, lst, curr);
			if (!curr)
				return (NULL);
		}
		else
			curr = curr->next;
	}
	return (curr);
}

t_token	*expand_quotes(t_token *lst)
{
	t_token	*curr;

	curr = lst;
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
	return (curr);
}

t_token	*remove_quotes(t_token **lst)
{
	t_token	*curr;
	t_token	*prev;

	curr = *lst;
	while (curr)
	{
		if (curr->type == QUOTE || curr->type == DQUOTE)
		{
			prev = token_find_prev(*lst, curr);
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			token_free(curr);
		}
		curr = curr->next;
	}
	return (curr);
}

t_token	*join_unspaced_words(t_token *t)
{
	t_token	*curr;

	curr = t;
	while (curr)
	{
		if (curr->type == WORD && !curr->space_after
			&& curr->next && curr->next->type == WORD)
			merge_word_tokens(curr, curr->next);
		curr = curr->next;
	}
}

t_token	*expansion(t_ht_table *ht, t_token **lst)
{
	expand_sigils(ht, lst);
	expand_quotes(*lst);
	remove_quotes(lst);
	// join_unspaced_words
	return (*lst);
}
