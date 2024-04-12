/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:34:37 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/12 17:33:46 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

/* Determine if the first 1 or 2 characters of the string are operators */
enum e_operator	get_operator(char *str, enum e_quotes is_quoted)
{
	if (is_quoted == NOT_QUOTED)
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
	}
	return (NOT_OPERATOR);
}

enum e_token	get_type(char *str, enum e_quotes is_quoted, enum e_operator op)
{
	if (str[0] == '\'' && is_quoted != DQUOTED)
		return (SQUOTE);
	else if (str[0] == '\"' && is_quoted != SQUOTED)
		return (DQUOTE);
	else if (str[0] == '~' && is_quoted == NOT_QUOTED)
		return (TILDE);
	else if (str[0] == '$' && (is_quoted == NOT_QUOTED || is_quoted == DQUOTED))
		return (SIGIL);
	else if (op != NOT_OPERATOR && is_quoted == NOT_QUOTED)
		return (OPERATOR);
	else if (ft_isdigit(str[0]))
		return (DIGIT);
	else if (!ft_isalpha(str[0]) && str[0] != ' ')
		return (OTHER);
	return (WORD);
}

/* Returns a pointer to a character in s that is present in set, or a pointer
to the last character. */
char	*ft_strset(char *s, char *set)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(set, s[i]))
			return ((char *)&s[i]);
		i++;
	}
	return (&s[i]);
}

inline int	is_valid_variable_char(int c)
{
	return (!ft_isalnum(c) && c != '_');
}

int 	find_end_of_variable_name(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_valid_variable_char(s[i]))
			return (&s[i] - s);
		i++;
	}
	return (&s[i] - s);
}

