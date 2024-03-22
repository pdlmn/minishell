/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/22 15:39:17 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	terminate(t_tlist *lst, char *str_to_free, char *message)
{
	if (str_to_free)
		free(str_to_free);
	if (lst)
		token_list_free(lst->head);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
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
		if (curr->type == WORD && !curr->space_after && tmp
			&& tmp->type == WORD)
		{
			content = ft_strjoin(curr->content, tmp->content);
			if (!content)
				terminate(lst, NULL, "Memory error\n");
			free(curr->content);
			curr->content = content;
			curr->space_after = tmp->space_after;
			curr->next = tmp->next;
			token_free(tmp);
		}
		else
			curr = curr->next;
	}
}

static inline t_token	*token_create_from_input(int *i, char *input,
		t_tlist *lst)
{
	char	*c;
	t_token	*token;

	if (ft_strchr("\"'", input[*i]))
	{
		c = dup_quoted(input[*i], i, input);
		if (ft_strlen(c) == 2)
		{
			free(c);
			return (NULL);
		}
	}
	else if (ft_strchr("><|", input[*i]))
		c = dup_operator(i, input);
	else
		c = dup_until_next_space(i, input);
	if (!c)
		terminate(lst, NULL, "Memory error\n");
	token = token_create(get_type(c), get_operator(c), c, input[*i] == ' ');
	if (!token)
		terminate(lst, c, "Memory error\n");
	return (token);
}

t_token	*lexer(char *input)
{
	t_tlist	lst;
	t_token	*token;
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
		token = token_create_from_input(&i, input, &lst);
		if (token)
			token_list_append(&lst, token);
		else
			lst.tail->space_after = input[i] == ' ';
	}
	concat_adjacent(&lst);
	return (lst.head);
}
