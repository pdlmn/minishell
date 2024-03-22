/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:36:25 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/22 17:10:58 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <stdio.h>

t_token	*token_create(enum e_token type, enum e_operator op, char *content,
		int space_after)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	res->next = NULL;
	res->type = type;
	res->op_type = op;
	res->content = content;
	res->space_after = space_after;
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
	char	*op;
	char	*type;

	while (t)
	{
		if (t->type == WORD)
			type = "WORD";
		else
			type = "OPERATOR";
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
		printf("{%s, %s, %s, %d}\n", t->content, type, op, t->space_after);
		t = t->next;
	}
}
