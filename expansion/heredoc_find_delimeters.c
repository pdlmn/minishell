/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_find_delimeters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:44 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/18 20:37:36 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token	*convert_to_delimeter(t_token *t)
{
	t_token			*curr;
	t_token			*delim;
	enum e_token	type;

	curr = t;
	type = DELIM;
	delim = NULL;
	while (curr)
	{
		if (curr->is_quoted == START_QUOTE)
			type = QDELIM;
		if (delim && curr->type != SQUOTE && curr->type != DQUOTE && curr->space_after)
			break ;
		else if (!delim && curr->type != SQUOTE && curr->type != DQUOTE)
			delim = curr;
		else
			curr = curr->next;
	}
	delim->type = type;
	return (delim);
}

t_tlist	*heredoc_find_delimeters(t_minishell *sh)
{
	t_token	*curr;

	curr = sh->lst.head;
	while (curr)
	{
		if (curr->op_type == HEREDOC && curr->next)
			convert_to_delimeter(curr->next);
		curr = curr->next;
	}
	return (&sh->lst);
}
