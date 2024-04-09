/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:36:25 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/09 14:59:25 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <stdio.h>

t_token	*token_create(char *content, int len, int space_after, enum e_quotes is_quoted)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	res->next = NULL;
	res->type = get_type(content);
	res->op_type = get_operator(content);
	res->content = content;
	res->len = len;
	res->space_after = space_after;
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
	char	*type;
	char	*op;
	char	*is_quoted;

	while (t)
	{
		if (t->type == WORD)
			type = "WORD";
		else if (t->type == OPERATOR)
			type = "OPERATOR";
		else if (t->type == QUOTE)
			type = "QUOTE";
		else if (t->type == DQUOTE)
			type = "DQUOTE";
		else if (t->type == TILDE)
			type = "TILDE";
		else if (t->type == SIGIL)
			type = "SIGIL";
		if (t->op_type == PIPE)
			op = "PIPE";
		else if (t->op_type == IN_REDIR)
			op = "IN_REDIR";
		else if (t->op_type == OUT_REDIR)
			op = "OUT_REDIR";
		else if (t->op_type == OUT_REDIR_APPEND)
			op = "OUT_REDIR_APPEND";
		else if (t->op_type == HEREDOC)
			op = "HEREDOC";
		else
			op = "NOT_OPERATOR";
		if (t->is_quoted == SQUOTED)
			is_quoted = "SQUOTED";
		else if (t->is_quoted == DQUOTED)
			is_quoted = "DQUOTED";
		else
			is_quoted = "NOT_QUOTED";
		printf("{%s, %s, %s, %s, %d}\n", t->content, type, op, is_quoted, t->space_after);
		t = t->next;
	}
}
