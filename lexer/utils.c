/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:34:37 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/22 15:53:35 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

/* Determine if the first 1 or 2 characters of the string are operators */
enum e_operator	get_operator(char *str)
{
	if (ft_strncmp(">>", str, 2) == 0)
		return (OUT_REDIR_APPEND);
	else if (ft_strncmp("<<", str, 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(">", str, 1) == 0)
		return (OUT_REDIR);
	else if (ft_strncmp("<", str, 1) == 0)
		return (IN_REDIR);
	else if (ft_strncmp("|", str, 1) == 0)
		return (PIPE);
	return (NOT_OPERATOR);
}

enum e_token	get_type(char *str)
{
	if (get_operator(str) == NOT_OPERATOR)
		return (WORD);
	return (OPERATOR);
}

char	*dup_quoted(char quote, int *i, char *input)
{
	int		j;
	char	*res;

	j = 1;
	while (input[*i + j])
	{
		if (input[*i + j++] == quote)
			break ;
	}
	res = ft_substr(input, *i, j);
	*i += j;
	return (res);
}

char	*dup_until_next_space(int *i, char *input)
{
	int		j;
	char	*res;

	j = 1;
	while (input[*i + j] && input[*i + j] != ' ' && input[*i + j] != '\''
		&& input[*i + j] != '"' && !ft_strchr("><|", input[*i + j]))
		j++;
	res = ft_substr(input, *i, j);
	*i += j;
	return (res);
}

char	*dup_operator(int *i, char *input)
{
	int				j;
	enum e_operator	op;
	char			*res;

	op = get_operator(&input[*i]);
	if (op == IN_REDIR || op == OUT_REDIR || op == PIPE)
		j = 1;
	else
		j = 2;
	res = ft_substr(input, *i, j);
	*i += j;
	return (res);
}
