/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:36:25 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/21 17:59:26 by emuminov         ###   ########.fr       */
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

void	token_list_free(t_token *lst)
{
	t_token	*curr;
	t_token	*tmp;

	curr = lst;
	while (curr)
	{
		tmp = curr->next;
		token_free(curr);
		curr = tmp;
	}
}

void	token_list_print(t_token *lst)
{
	t_token	*curr;
	char	operators[6][17] = {"NOT_OPERATOR", "IN_REDIR", "OUT_REDIR",
			"HEREDOC", "OUT_REDIR_APPEND", "PIPE"};
	char	type[2][9] = {"WORD", "OPERATOR"};

	curr = lst;
	while (curr)
	{
		printf("{%s, %s, %s, %d}\n", curr->content, type[curr->type],
			operators[curr->op_type], curr->space_after);
		curr = curr->next;
	}
}
