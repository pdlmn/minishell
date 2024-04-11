/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:36:25 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 15:56:21 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <stdio.h>

t_token	*token_create(char *content, int len, int space_after,
		enum e_quotes is_quoted)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	res->next = NULL;
	res->prev = NULL;
	res->type = get_type(content);
	res->op_type = get_operator(content);
	res->content = content;
	res->len = len;
	res->space_after = space_after;
	if ((res->type == SQUOTE || res->type == DQUOTE) && is_quoted == NOT_QUOTED)
		is_quoted = START_QUOTE;
	else if ((res->type == SQUOTE || res->type == DQUOTE)
			&& (is_quoted == SQUOTED || is_quoted == DQUOTED))
		is_quoted = END_QUOTE;
	res->is_quoted = is_quoted;
	return (res);
}

void	token_free(t_token *token)
{
	free(token->content);
	free(token);
}

void	token_list_append(t_tlist *lst, t_token *token)
{
	if (lst->head == NULL)
	{
		lst->head = token;
		lst->tail = token;
		return ;
	}
	token->prev = lst->tail;
	lst->tail->next = token;
	lst->tail = token;
}

void	token_list_free(t_token *token)
{
	t_token	*curr;
	t_token	*tmp;

	curr = token;
	while (curr)
	{
		tmp = curr->next;
		token_free(curr);
		curr = tmp;
	}
}

void	token_list_print(t_token *t)
{
	const char	*type[] = {"WORD", "OPERATOR", "QUOTE", "DQUOTE", "TILDE",
			"SIGIL"};
	const char	*op[] = {"NOT_OPERATOR", "IN_REDIR", "OUT_REDIR", "HEREDOC",
			"OUT_REDIR_APPEND", "PIPE"};
	const char	*is_quoted[] = {"NOT_QUOTED", "SQUOTED", "DQUOTED",
		"START_QUOTE", "END_QUOTE"};

	while (t)
	{
		printf("{%s, %s, %s, %s, %d}\n", t->content, type[t->type],
			op[t->op_type], is_quoted[t->is_quoted], t->space_after);
		t = t->next;
	}
}
