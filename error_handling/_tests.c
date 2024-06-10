/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:24:04 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/20 17:13:41 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <assert.h>

void	test_error_checking(t_minishell *sh, char *str,
		enum e_err_code expected_err_code, char *expected_token_content)
{
	t_err_src	e;

	lex_input(str, &sh->lst);
	e = check_errors(&sh->lst);
	printf("\n");
	printf("Err code:             %d\n", e.code);
	printf("Err code should be:   %d\n", expected_err_code);
	if (e.t)
		printf("Bad token:            %s\n", e.t->content);
	else
		printf("Bad token:            (null)\n");
	printf("Bad token should be:  %s\n", expected_token_content);
	token_list_print(&sh->lst);
	print_error_message(&e);
	assert(expected_err_code == e.code);
	if (e.t)
		assert(ft_strcmp(expected_token_content, e.t->content) == 0);
	else
		assert(e.t == NULL);
	token_list_free(&sh->lst);
}

int	main(void)
{
	static t_minishell	sh;

	test_error_checking(&sh, ">> example.txt", NO_ERRORS, NULL);
	test_error_checking(&sh, "> example.txt", NO_ERRORS, NULL);
	test_error_checking(&sh, "< example.txt", NO_ERRORS, NULL);
	test_error_checking(&sh, "<< EOF", NO_ERRORS, NULL);
	test_error_checking(&sh, ">> >", BAD_OPERAND, ">");
	test_error_checking(&sh, ">> |", BAD_OPERAND, "|");
	test_error_checking(&sh, "> |", BAD_OPERAND, "|");
	test_error_checking(&sh, "| |", BAD_OPERAND, "|");
	test_error_checking(&sh, "| cat", BAD_OPERAND, "|");
	test_error_checking(&sh, "cat << | EOF", BAD_OPERAND, "|");
	test_error_checking(&sh, ">", NO_OPERAND, NULL);
	test_error_checking(&sh, "<", NO_OPERAND, NULL);
	test_error_checking(&sh, ">>", NO_OPERAND, NULL);
	test_error_checking(&sh, "<<", NO_OPERAND, NULL);
	test_error_checking(&sh, "|", NO_OPERAND, NULL);
	test_error_checking(&sh, "cat example.txt |", NO_OPERAND, NULL);
	test_error_checking(&sh, "\"Hello", UNCLOSED_QUOTE, "\"");
	test_error_checking(&sh, "'Hello", UNCLOSED_QUOTE, "'");
	test_error_checking(&sh, "'Hello\"", UNCLOSED_QUOTE, "'");
	test_error_checking(&sh, "\"Hello\'", UNCLOSED_QUOTE, "\"");
}
