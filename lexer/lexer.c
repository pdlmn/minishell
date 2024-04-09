/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/09 17:40:55 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	set_is_quoted(t_tlist *lst, enum e_quotes *is_quoted)
{
	if (lst->tail->type == QUOTE && *is_quoted == NOT_QUOTED)
		*is_quoted = SQUOTED;
	else if (lst->tail->type == QUOTE && *is_quoted == SQUOTED)
		*is_quoted = NOT_QUOTED;
	if (lst->tail->type == DQUOTE && *is_quoted == NOT_QUOTED)
		*is_quoted = DQUOTED;
	else if (lst->tail->type == DQUOTE && *is_quoted == DQUOTED)
		*is_quoted = NOT_QUOTED;
}

t_token	*lexer(char *input)
{
	t_tlist			lst;
	t_token			*t;
	int				i;
	enum e_quotes	is_quoted;

	is_quoted = NOT_QUOTED;
	lst.head = NULL;
	lst.tail = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			i++;
			continue ;
		}
		t = token_create_from_input(&input[i], is_quoted);
		if (!t)
			return (NULL);
		token_list_append(&lst, t);
		i += lst.tail->len;
		set_is_quoted(&lst, &is_quoted);
	}
	return (lst.head);
}
