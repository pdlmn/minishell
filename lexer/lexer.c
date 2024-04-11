/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 20:21:09 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	set_is_quoted(t_token *t, enum e_quotes *is_quoted)
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

t_tlist	*token_list_init(void)
{
	t_tlist	*lst;

	lst = malloc(sizeof(t_tlist));
	if (!lst)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	return (lst);
}

t_token	*add_input_to_token_list(t_token *t, t_tlist *lst, char *current_char,
		enum e_quotes *is_quoted)
{
	t = token_create_from_input(t, current_char, *is_quoted);
	if (!t)
		return (NULL);
	token_list_append(lst, t);
	set_is_quoted(t, is_quoted);
	return (t);
}

t_tlist	*lexer(char *input)
{
	t_tlist			*lst;
	t_token			*t;
	enum e_quotes	is_quoted;
	int				i;

	lst = token_list_init();
	if (!lst)
		return (NULL);
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
		t = add_input_to_token_list(t, lst, &input[i], &is_quoted);
		if (!t)
			return (token_list_free(lst), NULL);
		i += t->len;
	}
	return (lst);
}
