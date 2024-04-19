/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/19 20:44:16 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static t_tlist	*token_list_convert_to_quoted(t_tlist *lst,
		enum e_quotes quotes_type)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->type != SIGIL)
		{
			curr->type = WORD;
			curr->op_type = NOT_OPERATOR;
		}
		curr->is_quoted = quotes_type;
		curr = curr->next;
	}
	return (lst);
}

t_tlist	*expand_heredoc(t_minishell *sh, t_tlist *lst, enum e_token type)
{
	if (type == DELIM)
		token_list_convert_to_quoted(lst, DQUOTED);
	else
		token_list_convert_to_quoted(lst, SQUOTED);
	if (!expand_variables(sh, lst))
		return (NULL);
	if (!expand_quotes(lst))
		return (NULL);
	return (lst);
}

t_tlist	*expand_tokens(t_minishell *sh, t_tlist *lst)
{
	if (!expand_variables(sh, lst))
		return (NULL);
	if (!expand_quotes(lst))
		return (NULL);
	if (!remove_quotes(lst))
		return (NULL);
	if (!join_unspaced_words(lst))
		return (NULL);
	return (&sh->lst);
}
