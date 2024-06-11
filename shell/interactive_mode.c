/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:51:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/11 21:32:20 by omougel          ###   ########.fr       */
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

	while (42)
	{
		init_interacrive_signal_handlers();
		input = read_command(PROMPT);
		if (input == NULL)
			return (ft_putstr_fd("exit\n", STDOUT_FILENO), sh_cleanup(sh, NULL,
					sh->env), 0);
		if (!lex_input(input, &sh->lst))
			return (sh_cleanup(sh, input, sh->env));
		if (!handle_prompt_syntax_errors(sh, input))
			continue ;
		sh->last_status = set_or_get_exit_status(GET, -1);
		if (!expand_tokens(sh, &sh->lst))
			return (sh_cleanup(sh, input, sh->env));
		if (!command_table(sh))
			return (sh_cleanup(sh, input, sh->env));
		if (sh->cmd_tab[0] && sh->cmd_tab[0][0])
			execute(*sh);
		sh_cleanup(sh, input, NULL);
	}
}
