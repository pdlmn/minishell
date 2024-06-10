/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 16:46:22 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static void	token_list_convert_to_quoted(t_tlist *lst,
		enum e_quotes quotes_type)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (ft_strcmp(curr->content, "$") == 0 && quotes_type != SQUOTED)
			curr->type = SIGIL;
		curr->is_quoted = quotes_type;
		curr = curr->next;
	}
}

static void	token_list_convert_quotes_to_words(t_tlist *lst)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->type == SQUOTE || curr->type == DQUOTE)
			token_convert_to_word(curr);
		curr = curr->next;
	}
}

t_tlist	*expand_heredoc(t_minishell *sh, t_tlist *lst, enum e_token type)
{
	if (type == DELIM)
		token_list_convert_to_quoted(lst, DQUOTED);
	else
		token_list_convert_to_quoted(lst, SQUOTED);
	if (!expand_variables(sh, lst))
		return (NULL);
	token_list_convert_quotes_to_words(lst);
	if (!join_unspaced_words(lst, 1))
		return (NULL);
	return (lst);
}

t_tlist	*expand_tokens(t_minishell *sh, t_tlist *lst)
{
	if (!expand_variables(sh, lst))
		return (NULL);
	if (!split_spaced_unqouted_tokens(lst))
		return (NULL);
	if (!expand_quotes(lst))
		return (NULL);
	if (!remove_quotes(lst))
		return (NULL);
	if (!join_unspaced_words(lst, 0))
		return (NULL);
	return (&sh->lst);
}
