/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/21 18:00:45 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	throw_empty_quotes(t_tlist *lst)
{
	t_token	*curr;
	t_token	*prev;

	curr = lst->head;
	prev = NULL;
	while (curr)
	{
		if (ft_strnstr(curr->content, "\"\"", 2) || ft_strnstr(curr->content,
				"''", 2))
		{
			if (prev)
			{
				if (prev->space_after == 0 && curr->space_after == 1)
					prev->space_after = curr->space_after;
				prev->next = curr->next;
				if (lst->tail == curr)
					lst->tail = prev;
				token_free(curr);
				curr = prev;
			}
			else
			{
				lst->head = curr->next;
				token_free(curr);
				curr = lst->head;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}

t_token	*token_concat_words(t_token *t1, t_token *t2)
{
	char	*content;

	content = ft_strjoin(t1->content, t2->content);
	if (!content)
		return (NULL);
	return token_create(WORD, NOT_OPERATOR, content, t2->space_after);
}

void	concat_adjacent(t_tlist *lst)
{
	t_token	*curr;
	t_token	*tmp;
	char	*content;

	curr = lst->head;
	while (curr)
	{
		tmp = curr->next;
		if (curr->type == WORD && !curr->space_after && tmp && tmp->type == WORD)
		{
			content = ft_strjoin(curr->content, tmp->content);
			free(curr->content);
			curr->content = content;
			curr->space_after = tmp->space_after;
			curr->next = tmp->next;
			free(tmp->content);
			free(tmp);
		}
		else
			curr = curr->next;
	}
}

t_token	*lexer(char *input)
{
	t_tlist	lst;
	t_token	*token;
	char	*content;
	int		i;

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
		else if (input[i] == '\'' || input[i] == '"')
		{
			content = dup_quoted(input[i], &i, input);
			// if (!raw_token) handle error
			token = token_create(WORD, NOT_OPERATOR, content, input[i] == ' ');
			// if (!token) handle error
			token_list_append(&lst, token);
		}
		else if (ft_strchr("><|", input[i]))
		{
			content = dup_operator(&i, input);
			// if (!raw_token) handle error
			token = token_create(OPERATOR, determine_operator(content), content,
					input[i] == ' ');
			// if (!token) handle error
			token_list_append(&lst, token);
		}
		else
		{
			content = dup_until_next_space(&i, input);
			// if (!raw_token) handle error
			token = token_create(WORD, NOT_OPERATOR, content, input[i] == ' ');
			// if (!token) handle error
			token_list_append(&lst, token);
		}
	}
	throw_empty_quotes(&lst);
	concat_adjacent(&lst);
	return (lst.head);
}
