/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:35:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/09 17:41:40 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

static int	find_end_of_word(char *s, enum e_quotes is_quoted)
{
	if (is_quoted == SQUOTED)
		return (ft_strset(s, "'") - s);
	else if (is_quoted == DQUOTED)
		return (ft_strset(s, "\"$") - s);
	return (ft_strset(s, "\"'$><| ") - s);
}

static t_token	*create_single_char_token(char *input, enum e_quotes is_quoted)
{
	t_token	*t;
	char	*s;

	s = ft_substr(input, 0, 1);
	t = token_create(s, 1, input[1] == ' ', is_quoted);
	return (t);
}

static t_token	*create_operator_token(char *input, enum e_quotes is_quoted)
{
	int						len;
	const enum e_operator	op = get_operator(input);
	char					*s;
	t_token					*t;

	if (op == IN_REDIR || op == OUT_REDIR || op == PIPE)
		len = 1;
	else
		len = 2;
	s = ft_substr(input, 0, len);
	t = token_create(s, len, input[len] == ' ', is_quoted);
	return (t);
}

static t_token	*create_word_token(char *input, enum e_quotes is_quoted)
{
	int		i;
	char	*s;
	t_token	*t;

	i = find_end_of_word(input, is_quoted);
	s = ft_substr(input, 0, i);
	t = token_create(s, i, input[i] == ' ', is_quoted);
	return (t);
}

t_token	*token_create_from_input(char *input,
		enum e_quotes is_quoted)
{
	t_token	*t;

	if ((is_quoted != SQUOTED && *input == SIGIL_CHAR)
		|| (is_quoted == NOT_QUOTED && ft_strchr(NON_OPERATOR_SYMBOLS, *input))
		|| (is_quoted == SQUOTED && *input == QUOTE_CHAR)
		|| (is_quoted == DQUOTED && *input == DQUOTE_CHAR))
		t = create_single_char_token(input, is_quoted);
	else if (is_quoted == NOT_QUOTED && ft_strchr(OPERATOR_SYMBOLS, *input))
		t = create_operator_token(input, is_quoted);
	else
		t = create_word_token(input, is_quoted);
	if (!t)
		return (NULL);
	return (t);
}
