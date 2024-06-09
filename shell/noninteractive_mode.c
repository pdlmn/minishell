/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_mode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:52:00 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/09 16:52:26 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	launch_noninteractive_mode(t_minishell *sh, char **argv)
{
	init_exec_signal_handlers();
	if (argv[1] && ft_strcmp(argv[1], "-c") != 0)
	{
		ft_putstr_fd("mishell: incorrect usage\n", STDERR_FILENO);
		return (sh_cleanup(sh, NULL));
	}
	if (!lex_input(argv[2], &sh->lst))
		return (sh_cleanup(sh, NULL));
	if (!handle_prompt_syntax_errors(sh, argv[2]))
		return (sh_cleanup(sh, NULL));
	sh->last_status = set_or_get_exit_status(GET, -1);
	if (!expand_tokens(sh, &sh->lst))
		return (sh_cleanup(sh, NULL));
	if (!command_table(sh))
		return (sh_cleanup(sh, NULL));
	if (sh->cmd_tab[0][0])
		execute(*sh);
	sh_cleanup(sh, NULL);
	return (EXIT_SUCCESS);
}
