/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:36:25 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/04 16:57:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_create(char *content, int len, int space_after,
		enum e_quotes is_quoted)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	res->op_type = get_operator(content, is_quoted);
	res->type = get_type(content, is_quoted, res->op_type);
	res->is_quoted = is_quoted;
	res->next = NULL;
	res->prev = NULL;
	res->content = content;
	res->len = len;
	res->space_after = space_after;
	return (res);
}

void	token_list_append(t_tlist *lst, t_token *t)
{
	if (lst->head == NULL)
	{
		lst->head = t;
		lst->tail = t;
		return ;
	}
	t->prev = lst->tail;
	lst->tail->next = t;
	lst->tail = t;
}

void	token_list_print(t_tlist *lst)
{
	const char	*type[] = {"WORD", "OPERATOR", "QUOTE", "DQUOTE", "TILDE",
		"SIGIL", "DIGIT", "QMARK", "DELIM", "QDELIM", "OTHER"};
	const char	*op[] = {"NOT_OPERATOR", "IN_REDIR", "OUT_REDIR", "HEREDOC",
		"OUT_REDIR_APPEND", "PIPE"};
	const char	*is_quoted[] = {"NOT_QUOTED", "SQUOTED", "DQUOTED",
		"START_QUOTE", "END_QUOTE"};
	t_token		*t;

	t = lst->head;
	while (t)
	{
		printf("{%s, %s, %s, %s, %d}\n", t->content, type[t->type],
			op[t->op_type], is_quoted[t->is_quoted], t->space_after);
		t = t->next;
	}
}
