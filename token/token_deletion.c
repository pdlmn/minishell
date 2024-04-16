/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_deletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:09:54 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/16 20:41:05 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_free(t_token *t)
{
	free(t->content);
	free(t);
}

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

void	token_list_free(t_tlist *lst)
{
	t_token	*curr;
	t_token	*tmp;

	curr = lst->head;
	while (curr)
	{
		tmp = curr->next;
		token_free(curr);
		curr = tmp;
	}
	lst->head = NULL;
	lst->tail = NULL;
}
