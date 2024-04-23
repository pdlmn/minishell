/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:35:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/04 17:20:25 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

static t_token	*create_single_char_token(t_token *last_t, char *input,
		enum e_quotes is_quoted)
{
	t_token				*t;
	char				*s;
	const enum e_token	type = get_type(input, is_quoted, NOT_OPERATOR);
	const enum e_quotes	old_is_quoted = is_quoted;

	if ((type == SQUOTE || type == DQUOTE) && is_quoted == NOT_QUOTED)
		is_quoted = START_QUOTE;
	else if ((type == SQUOTE && is_quoted == SQUOTED)
		|| (type == DQUOTE && is_quoted == DQUOTED))
		is_quoted = END_QUOTE;
	if (is_quoted == END_QUOTE
		&& last_t && last_t->is_quoted == START_QUOTE)
	{
		s = ft_calloc(1, sizeof(char));
		is_quoted = old_is_quoted;
	}
	else
		s = ft_substr(input, 0, 1);
	if (!s)
		return (NULL);
	t = token_create(s, ft_strlen(s), ft_isspace(input[1]), is_quoted);
	if (!t)
		return (free(s), NULL);
	return (t);
}

static t_token	*create_operator_token(char *input, enum e_quotes is_quoted)
{
	int						len;
	const enum e_operator	op = get_operator(input, is_quoted);
	char					*s;
	t_token					*t;

	if (op == IN_REDIR || op == OUT_REDIR || op == PIPE)
		len = 1;
	else
		len = 2;
	s = ft_substr(input, 0, len);
	if (!s)
		return (NULL);
	t = token_create(s, len, ft_isspace(input[len]), is_quoted);
	if (!t)
		return (free(s), NULL);
	return (t);
}

static t_token	*create_word_token(t_token *last_t, char *input,
		enum e_quotes is_quoted)
{
	int		end_of_word;
	char	*s;
	t_token	*t;

	if (is_quoted == SQUOTED && (!last_t || (last_t
				&& last_t->type != SIGIL)))
		end_of_word = ft_strset(input, "'$") - input;
	else if (is_quoted == SQUOTED && last_t && last_t->type == SIGIL)
		end_of_word = find_end_of_variable_name(input);
	else if (is_quoted == DQUOTED && (!last_t || (last_t
				&& last_t->type != SIGIL)))
		end_of_word = ft_strset(input, "\"$") - input;
	else if (is_quoted == DQUOTED && last_t && last_t->type == SIGIL)
		end_of_word = find_end_of_variable_name(input);
	else
		end_of_word = ft_strset(input, "\"'$><| ") - input;
	s = ft_substr(input, 0, end_of_word);
	if (!s)
		return (NULL);
	t = token_create(s, end_of_word, ft_isspace(input[end_of_word]), is_quoted);
	if (!t)
		return (free(s), NULL);
	t->type = WORD;
	return (t);
}

t_token	*token_create_from_input(t_token *last_t, char *input,
		enum e_quotes is_quoted)
{
	t_token	*t;

	if ((is_quoted == NOT_QUOTED && ft_strchr("><|", input[0])))
		t = create_operator_token(input, is_quoted);
	else if ((is_quoted == NOT_QUOTED && ft_strchr("\"'~$", input[0]))
		|| (is_quoted == DQUOTED && input[0] == '"')
		|| (is_quoted == SQUOTED && input[0] == '\'')
		|| input[0] == '$'
		|| ((ft_isdigit(input[0]) || input[0] == '?')
			&& last_t && last_t->type == SIGIL)
		|| (!is_valid_variable_char(input[0]) && input[0] != ' '))
		t = create_single_char_token(last_t, input, is_quoted);
	else
		t = create_word_token(last_t, input, is_quoted);
	if (!t)
		return (NULL);
	return (t);
}
