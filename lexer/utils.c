/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:34:37 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 20:14:25 by emuminov         ###   ########.fr       */
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

enum e_token	get_type(char *str, enum e_quotes is_quoted)
{
	if (str[0] == '\'' && is_quoted != DQUOTED)
		return (SQUOTE);
	else if (str[0] == '\"' && is_quoted != SQUOTED)
		return (DQUOTE);
	else if (str[0] == '~' && is_quoted == NOT_QUOTED)
		return (TILDE);
	else if (str[0] == '$' && is_quoted == NOT_QUOTED)
		return (SIGIL);
	else if (get_operator(str) != NOT_OPERATOR && is_quoted == NOT_QUOTED)
		return (OPERATOR);
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

void	terminate(t_tlist *lst, char *str_to_free, char *message)
{
	if (str_to_free)
		free(str_to_free);
	if (lst)
		token_list_free(lst);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
