/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/21 13:37:40 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

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
	return (lst.head);
}
