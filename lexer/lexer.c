/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/20 13:29:24 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

static void	set_is_quoted(t_token *t, enum e_quotes *is_quoted)
{
	if (t->type == SQUOTE && *is_quoted == NOT_QUOTED)
		*is_quoted = SQUOTED;
	else if (t->type == SQUOTE && *is_quoted == SQUOTED)
		*is_quoted = NOT_QUOTED;
	if (t->type == DQUOTE && *is_quoted == NOT_QUOTED)
		*is_quoted = DQUOTED;
	else if (t->type == DQUOTE && *is_quoted == DQUOTED)
		*is_quoted = NOT_QUOTED;
}

t_tlist	*lex_input(char *input, t_tlist *lst)
{
	t_token			*t;
	enum e_quotes	is_quoted;
	int				i;

	t = NULL;
	is_quoted = NOT_QUOTED;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' && is_quoted == NOT_QUOTED)
		{
			i++;
			continue ;
		}
		t = token_create_from_input(t, &input[i], is_quoted);
		if (!t)
			return (token_list_free(lst), NULL);
		token_list_append(lst, t);
		set_is_quoted(t, &is_quoted);
		i += t->len;
	}
	heredoc_find_delimeters(lst);
	return (lst);
}

t_tlist	*lex_heredoc_input(char *input, t_tlist *lst, enum e_token delim_type)
{
	t_token			*t;
	enum e_quotes	is_quoted;
	int				i;

	t = NULL;
	if (delim_type == DELIM)
		is_quoted = DQUOTED;
	else
		is_quoted = SQUOTED;
	i = 0;
	while (input[i])
	{
		t = token_create_from_input(t, &input[i], is_quoted);
		if (!t)
			return (token_list_free(lst), NULL);
		token_list_append(lst, t);
		i += t->len;
	}
	return (lst);
}
