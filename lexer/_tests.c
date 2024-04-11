/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:29:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 16:15:24 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_tlist	*lst;

	if (argc != 2)
	{
		printf("Enter proper command\n");
		return (EXIT_FAILURE);
	}
	lst = lexer(argv[1]);
	token_list_print(lst);
	token_list_free(lst);
}
