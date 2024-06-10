/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:51:27 by emuminov          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/09 17:03:33 by emuminov         ###   ########.fr       */
=======
/*   Updated: 2024/06/10 14:03:00 by emuminov         ###   ########.fr       */
>>>>>>> 14d64cd (feat: added changes from out school repo, added valgrind rule in makefile)
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*read_command(char *prompt)
{
	char	*command;

	command = readline(prompt);
	if (!command)
		return (NULL);
	add_history(command);
	return (command);
}

int	launch_interacrive_mode(t_minishell *sh)
{
	char	*input;

<<<<<<< HEAD
	init_interacrive_signal_handlers();
	while (42)
	{
=======
	while (42)
	{
		init_interacrive_signal_handlers();
>>>>>>> 14d64cd (feat: added changes from out school repo, added valgrind rule in makefile)
		input = read_command(PROMPT);
		if (input == NULL)
			return (ft_putstr_fd("exit\n", STDOUT_FILENO), sh_cleanup(sh, NULL,
					sh->env));
		if (!lex_input(input, &sh->lst))
			return (sh_cleanup(sh, input, sh->env));
		if (!handle_prompt_syntax_errors(sh, input))
			continue ;
		sh->last_status = set_or_get_exit_status(GET, -1);
		if (!expand_tokens(sh, &sh->lst))
			return (sh_cleanup(sh, input, sh->env));
		if (!command_table(sh))
			return (sh_cleanup(sh, input, sh->env));
		if (sh->cmd_tab[0][0])
			execute(*sh);
		sh_cleanup(sh, input, NULL);
	}
}
