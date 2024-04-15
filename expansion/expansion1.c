/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/15 20:26:38 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

t_token	*token_delete(t_tlist *lst, t_token *t)
{
	if (t->next)
		t->next->prev = t->prev;
	if (t->prev)
		t->prev->next = t->next;
	if (t == lst->head)
		lst->head = t->next;
	if (t == lst->tail)
		lst->tail = t->prev;
	return (t);
}

t_token	*token_delete_and_free(t_tlist *lst, t_token *t)
{
	t_token	*res;

	if (!t)
		return (NULL);
	res = t->next;
	token_delete(lst, t);
	token_free(t);
	return (res);
}

t_token	*token_convert_to_empty_word(t_token *t)
{
	t->type = WORD;
	t->content[0] = '\0';
	t->len = 0;
	return (t);
}

t_token	*delete_sigil_and_the_next_word(t_tlist *lst, t_token *sigil)
{
	t_token	*res;

	res = token_delete_and_free(lst, sigil);
	if (res->next)
		res = token_delete_and_free(lst, res);
	else
		token_convert_to_empty_word(res);
	return (res);
}

t_token	*replace_variable_with_value(t_tlist *lst,  t_token *sigil, char *val)
{
	char	*copied_val;
	t_token	*res;

	copied_val = ft_strdup(val);
	if (!copied_val)
		return (NULL);
	free(sigil->next->content);
	res = sigil->next;
	res->content = copied_val;
	res->len = ft_strlen(copied_val);
	token_delete(lst, sigil);
	token_free(sigil);
	return (res);
}

t_token	*token_convert_to_word(t_token *t)
{
	t->type = WORD;
	return (t);
}

t_token	*expand_after_sigil(t_tlist *lst, t_ht_table *ht, t_token *sigil)
{
	char	*val;

	if (!sigil->space_after && sigil->next
		&& sigil->next->op_type == NOT_OPERATOR)
	{
		if (sigil->next->type == DIGIT)
			return (delete_sigil_and_the_next_word(lst, sigil));
		if (sigil->next->type == WORD)
		{
			val = ht_get(ht, sigil->next->content);
			if (!val)
				return (delete_sigil_and_the_next_word(lst, sigil));
			return (replace_variable_with_value(lst, sigil, val));
		}
		else if ((sigil->next->type == SQUOTE || sigil->next->type == DQUOTE)
				&& sigil->is_quoted == NOT_QUOTED)
			return (token_delete_and_free(lst, sigil));
		else if ((sigil->next->type == DQUOTE && sigil->is_quoted == DQUOTED)
				|| sigil->next->type == OTHER)
			return (token_convert_to_word(sigil));
	}
	return (token_convert_to_word(sigil));
}

t_token	*expand_tilde(t_ht_table *ht, t_token *tilde)
{
	char	*home_path;
	char	*cloned_home_path;

	home_path = ht_get(ht, "HOME");
	if (!home_path)
		return (token_convert_to_empty_word(tilde));
	cloned_home_path = ft_strdup(home_path);
	if (!cloned_home_path)
		return (NULL);
	free(tilde->content);
	tilde->type = WORD;
	tilde->content = cloned_home_path;
	tilde->len = ft_strlen(cloned_home_path);
	return (tilde);
}

t_tlist	*expand_variables(t_tlist *lst, t_ht_table *ht)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->type == SIGIL)
			curr = expand_after_sigil(lst, ht, curr);
		else if (curr->type == TILDE)
			curr = expand_tilde(ht, curr);
		if (!curr)
			return (NULL);
		else
			curr = curr->next;
	}
	return (lst);
}

// TODO: evaluate if I need to put a space after
t_token	*merge_word_tokens(t_token *t1, t_token *t2)
{
	char	*s;
	int		len;

	len = t1->len + t2->len;
	s = malloc(sizeof(char) * (len + t1->space_after + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, t1->content, sizeof(char) * t1->len);
	if (t1->space_after && t1->is_quoted == NOT_QUOTED)
		s[t1->len] = ' ';
	ft_memcpy(&s[t1->len + (t1->space_after * (t1->is_quoted == NOT_QUOTED))], t2->content, sizeof(char) * t2->len);
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

t_token	*join_quotes_content(t_token *quote_token)
{
	t_token	*curr;

	curr = quote_token->next;
	while (curr)
	{
		if (curr->is_quoted == END_QUOTE)
			return (curr);
		else if ((curr->type == WORD || curr->type == OTHER)
				&& curr->next
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
	return (lst);
}
