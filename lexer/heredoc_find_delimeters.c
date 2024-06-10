/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_find_delimeters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:44 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/04 17:15:52 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	type_delim(t_token *t)
{
	t_token			*curr;
	enum e_token	type;

	curr = t;
	type = DELIM;
	while (curr && (!curr->space_after || curr->is_quoted != START_QUOTE))
	{
		if (curr->type == DQUOTE)
		{
			type = QDELIM;
			break ;
		}
		curr = curr->next;
	}
	return (type);
}

static t_token	*convert_to_delimeter(t_token *t)
{
	t_token				*curr;
	const enum e_token	type = type_delim(t);

	curr = t;
	while (curr)
	{
		if (curr->type != DQUOTE && curr->type != SQUOTE
			&& curr->type != OPERATOR)
			curr->type = type;
		if (curr->space_after && (curr->type != DQUOTE && curr->type != SQUOTE))
			break ;
		curr = curr->next;
	}
	return (curr);
}

void	heredoc_find_delimeters(t_tlist *lst)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->op_type == HEREDOC && curr->next)
			curr = convert_to_delimeter(curr->next);
		else
			curr = curr->next;
	}
}
