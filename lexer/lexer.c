/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:09:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/19 17:20:36 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/minishell.h"

// "e""c""h""o" ""hel'"l"'ooo""
// 'e''c''h''o' ""hel'"l"'ooo'' 

// echo "hel"
// 0123456789

// echo ""
// 0123456

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

enum e_operator_type	determine_operator(char *token)
{
	char	operators[5][3] = {">", "<", ">>", "<<", "|"};

	return (NOT_OPERATOR);
}

char	*dup_until_next_space(int *i, char *input)
{
	int		j;
	char	*res;

	j = 1;
	// TODO: add operators as well to the list
	while (input[*i + j] && input[*i + j] != ' ' && input[*i + j] != '\'' && input[*i + j] != '"')
		j++;
	res = ft_substr(input, *i, j);
	*i += j;
	return (res);
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
		else
		{
			raw_token = dup_until_next_space(&i, input);
			printf("word: %s\n", raw_token);
		}
	}
}

int	main()
{
	lexer("echo \"hello\"    ' \"\"\"''\"'hello'\"''\"\"\"  asdasda zxc qw a \"QUOTED AGAIN A\" 'small quote'");
}
