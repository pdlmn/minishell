/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:28:24 by omougel           #+#    #+#             */
/*   Updated: 2024/06/01 23:29:24 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command_table.h"

int	main(int argc, char **argv)
{
	static t_minishell	sh;
	char				***cmd_tab;
	size_t				i;

	i = 0;
	if (argc != 2)
	{
		printf("Enter proper command\n");
		return (EXIT_FAILURE);
	}
	lexer(argv[1], &sh);
	token_list_print(&sh.lst);
	cmd_tab = command_table(sh.lst.head);
	if (!cmd_tab)
		return (EXIT_FAILURE);
	while (cmd_tab && cmd_tab[i])
		print_arr(cmd_tab[i++]);
	ft_free_table(cmd_tab);
	token_list_free(&sh.lst);
}
