/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/20 16:07:24 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

/* Determine if the first 1 or 2 characters of the string are operators */
enum e_operator	determine_operator(char *str)
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
	// TODO: add operators as well to the list
	while (input[*i + j] && input[*i + j] != ' ' && input[*i + j] != '\'' && input[*i + j] != '"' && !ft_strchr("><|", input[*i + j]))
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

	op = determine_operator(&input[*i]);
	if (op == IN_REDIR || op == OUT_REDIR || op == PIPE)
		j = 1;
	else
		j = 2;
	res = ft_substr(input, *i, j);
	*i += j;
	return (res);
}

t_token	*token_init()
{
	
}

t_token	*token_create()
{
	
}

void	token_append()
{
	
}

void	token_free()
{

}

void	lexer(char *input)
{
	int		i;
	char	*raw_token;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
		{
			i++;
			continue;
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			raw_token = dup_quoted(input[i], &i, input);
			printf("quoted: %s\n", raw_token);
		}
		else if (ft_strchr("><|", input[i]))
		{
			raw_token = dup_operator(&i, input);
			printf("operator: %s\n", raw_token);
		}
		else
		{
			raw_token = dup_until_next_space(&i, input);
			printf("word: %s\n", raw_token);
		}
	}
}

int	main()
{
	lexer("echo <\"hello\"  >>>| \"\"\"''\"'hello'\"''\"\"\" | | asdasda zxc <<qw|a \"QUOTED AGAIN A\" 'small quote'");
}
