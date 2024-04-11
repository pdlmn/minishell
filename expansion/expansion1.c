/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 20:18:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

// input -> tokenization -> checking for errors -> expansion -> command_table

/* 1. Replace non singly-quoted $ values.
 * 2. Join all strings.
 * 3. Remove empty quotes.
 * 4.
 * 5. */

t_token	*expand_after_sigil(t_tlist *lst, t_ht_table *ht, t_token *sigil_t)
{
	char	*val;
	char	*copied_val;
	t_token	*res;

	if (!sigil_t->space_after && sigil_t->next
		&& sigil_t->next->op_type == NOT_OPERATOR)
	{
		if (sigil_t->next->type == WORD)
		{
			// delete SIGIL, replace contents of the next word with cloned ht value
			val = ht_get(ht, sigil_t->next->content);
			copied_val = ft_strdup(val);
			if (!copied_val)
				return (NULL);
			free(sigil_t->next->content);
			res = sigil_t->next;
			res->content = copied_val;
			res->len = ft_strlen(copied_val);
			if (sigil_t->prev)
			{
				sigil_t->prev->next = res;
				res->prev = sigil_t->prev;
			}
			else
			{
				lst->head = sigil_t->next;
				res->prev = NULL;
			}
			token_free(sigil_t);
			return (res);
		}
		else if ((sigil_t->next->type == SQUOTE || sigil_t->next->type == DQUOTE)
				&& sigil_t->is_quoted == NOT_QUOTED)
		{
			// delete SIGIL
			res = sigil_t->next;
			if (sigil_t->prev)
			{
				sigil_t->prev->next = res;
				res->prev = sigil_t->prev;
			}
			else
			{
				lst->head = sigil_t->next;
				res->prev = NULL;
			}
			token_free(sigil_t);
			return (res);
		}
		else if (sigil_t->next->type == DQUOTE && sigil_t->is_quoted == DQUOTED)
		{
			// convert SIGIL to word
			sigil_t->type = WORD;
			sigil_t->space_after = 0;
			return (sigil_t);
		}
	}
	else if (sigil_t->space_after || !sigil_t->next)
	{
		// convert SIGIL to word
		sigil_t->type = WORD;
		sigil_t->space_after = 0;
		return (sigil_t);
	}
	return (sigil_t);
}

t_tlist	*expand_variables(t_tlist *lst, t_ht_table *ht)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->type == SIGIL)
		{
			curr = expand_after_sigil(lst, ht, curr);
			if (!curr)
				return (NULL);
		}
		else
			curr = curr->next;
	}
	return (lst);
}

t_token	*merge_word_tokens(t_token *t1, t_token *t2)
{
	char	*s;
	int		len;

	len = t1->len + t2->len;
	s = malloc(sizeof(char) * (len + t1->space_after + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, t1->content, sizeof(char) * t1->len);
	if (t1->space_after)
		s[t1->len] = ' ';
	ft_memcpy(&s[t1->len + t1->space_after], t2->content, sizeof(char) * t2->len);
	s[len] = '\0';
	free(t1->content);
	t1->content = s;
	t1->len = len;
	t1->next = t2->next;
	if (t2->next)
		t2->next->prev = t1;
	return (token_free(t2), t1);
}

t_token	*join_quotes_content(t_token *quote_token)
{
	t_token	*curr;

	curr = quote_token->next;
	while (curr)
	{
		if (curr->is_quoted == END_QUOTE)
			return (curr);
		else if (curr->type == WORD && curr->next && curr->next->type == WORD)
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

/* Join everything inside the quotes. */
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
	t_token	*tmp;

	curr = lst->head;
	while (curr)
	{
		if (curr->type == SQUOTE || curr->type == DQUOTE)
		{
			if (curr->prev)
			{
				curr->prev->next = curr->next;
				if (curr->next)
					curr->next->prev = curr->prev;
			}
			else
			{
				lst->head = curr->next;
				if (curr->next)
					curr->next->prev = NULL;
			}
			tmp = curr->next;
			token_free(curr);
			curr = tmp;
		}
		else
			curr = curr->next;
	}
	if (tmp == NULL)
		lst->tail = NULL;
	return (lst);
}

t_tlist	*join_unspaced_words(t_tlist *lst)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->type == WORD && !curr->space_after
			&& curr->next && curr->next->type == WORD)
		{
			curr = merge_word_tokens(curr, curr->next);
			if (!curr)
				return (NULL);
		}
		curr = curr->next;
	}
	return (lst);
}

/* If a token list is empty, add one empty symbolic token. */
t_tlist	*handle_empty_token_list(t_tlist *lst)
{
	t_token *empty_t;
	char	 *s;

	if (lst->head != NULL)
		return (lst);
	s = ft_calloc(sizeof(char), 1);
	if (!s)
		return (NULL);
	empty_t = token_create(s, 0, 0, NOT_QUOTED);
	token_list_append(lst, empty_t);
	return (lst);
}

t_tlist	*expansion(t_tlist *lst, t_ht_table *ht)
{
	if (!expand_variables(lst, ht))
		return (NULL);
	if (!expand_quotes(lst))
		return (NULL);
	if (!remove_quotes(lst))
		return (NULL);
	if (!join_unspaced_words(lst))
		return (NULL);
	if (!handle_empty_token_list(lst))
		return (NULL);
	return (lst);
}
