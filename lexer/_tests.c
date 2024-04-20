/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:29:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/20 13:30:12 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	static t_minishell	sh;

	if (argc != 2)
	{
		printf("Enter proper command\n");
		return (EXIT_FAILURE);
	}
	lex_input(argv[1], &sh.lst);
	token_list_print(&sh.lst);
	token_list_free(&sh.lst);
}
