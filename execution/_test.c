/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:56:50 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 12:57:47 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	int			i;

	if (argc != 2)
		return (0);
	i = 0;
	minishell.env = envp;
	minishell.lst = lexer(argv[1]);
	token_list_print(minishell.lst);
	ft_printf("\n\n\n\n");
	minishell.cmd_tab = command_table(minishell.lst);
	if (!minishell.cmd_tab)
		return (EXIT_FAILURE);
	while (minishell.cmd_tab && minishell.cmd_tab[i])
		print_arr(minishell.cmd_tab[i++]);
	minishell.last_status = execute(minishell);
	token_list_free(minishell.lst);
	ft_free_table(minishell.cmd_tab);
	return (minishell.last_status);
}
