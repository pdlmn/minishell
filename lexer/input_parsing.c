/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:35:02 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/16 18:20:50 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

static t_token	*create_single_char_token(char *input, enum e_quotes is_quoted)
{
	t_token	*t;
	char	*s;

	s = ft_substr(input, 0, 1);
	if (!s)
		return (NULL);
	t = token_create(s, 1, input[1] == ' ', is_quoted);
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
	t = token_create(s, len, input[len] == ' ', is_quoted);
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

	if (is_quoted == SQUOTED)
		end_of_word = ft_strset(input, "'") - input;
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
	t = token_create(s, end_of_word, input[end_of_word] == ' ', is_quoted);
	if (!t)
		return (free(s), NULL);
	t->type = WORD;
	return (t);
}

t_token	*token_create_from_input(t_token *last_t, char *input,
		enum e_quotes is_quoted)
{
	t_token	*t;

	if ((is_quoted == NOT_QUOTED && ft_strchr("><|", *input)))
		t = create_operator_token(input, is_quoted);
	else if ((is_quoted == NOT_QUOTED && ft_strchr("\"'~$", *input))
		|| (is_quoted == DQUOTED && input[0] == '"')
		|| (is_quoted == SQUOTED && input[0] == '\'')
		|| (is_quoted != SQUOTED && input[0] == '$')
		|| (is_quoted != SQUOTED && ft_isdigit(input[0]) && last_t
			&& last_t->type == SIGIL) || ((is_quoted == NOT_QUOTED
				|| is_quoted == DQUOTED) && !is_valid_variable_char(*input)
			&& *input != ' '))
		t = create_single_char_token(input, is_quoted);
	else
		t = create_word_token(last_t, input, is_quoted);
	if (!t)
		return (NULL);
	return (t);
}
