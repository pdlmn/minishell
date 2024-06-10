/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 16:29:12 by emuminov         ###   ########.fr       */
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

static t_token	*split_spaced_token(t_token *token)
{
	char	**words;
	int		i;
	t_tlist	tmp_lst;
	t_token	*new_token;

	tmp_lst.head = NULL;
	tmp_lst.tail = NULL;
	words = ft_split(token->content, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		new_token = token_create(words[i], ft_strlen(words[i]), 1, NOT_QUOTED);
		if (!new_token)
			return (token_list_free(&tmp_lst), NULL);
		token_list_append(&tmp_lst, new_token);
		i++;
	}
	free(words);
	return (tmp_lst.head);
}

t_tlist	*split_spaced_unqouted_tokens(t_tlist *lst)
{
	t_token	*curr;
	t_token	*next;
	t_token	*first_new_token;

	curr = lst->head;
	while (curr)
	{
		if ((curr->is_quoted == NOT_QUOTED) && ft_strchr(curr->content, ' '))
		{
			first_new_token = split_spaced_token(curr);
			if (!first_new_token)
				return (NULL);
			next = curr->next;
			token_insert_tokens(lst, curr, first_new_token);
			token_free(curr);
			curr = next;
			continue;
		}
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
