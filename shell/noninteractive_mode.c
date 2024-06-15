/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noninteractive_mode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:52:00 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/15 17:39:01 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	launch_noninteractive_mode(t_minishell *sh, char **argv)
{
	init_exec_signal_handlers();
	if (argv[1] && ft_strcmp(argv[1], "-c") != 0)
	{
		ft_putstr_fd("mishell: incorrect usage\n", STDERR_FILENO);
		return (sh_cleanup(sh, NULL, sh->env));
	}
	if (!lex_input(argv[2], &sh->lst))
		return (sh_cleanup(sh, NULL, sh->env));
	if (!handle_prompt_syntax_errors(sh, NULL))
		return (sh_cleanup(sh, NULL, sh->env));
	sh->last_status = set_or_get_exit_status(GET, -1);
	if (!expand_tokens(sh, &sh->lst))
		return (sh_cleanup(sh, NULL, sh->env));
	if (check_if_the_first_arg_is_a_pathname(&sh->lst)
			&& handle_pathname_as_a_first_arg(sh, NULL))
		return (set_or_get_exit_status(GET, -1));
	if (!command_table(sh))
		return (sh_cleanup(sh, NULL, sh->env));
	if (sh->cmd_tab[0] && sh->cmd_tab[0][0])
		execute(*sh);
	sh_cleanup(sh, NULL, NULL);
	return (set_or_get_exit_status(GET, -1));
}
