/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:51:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/09 16:53:46 by emuminov         ###   ########.fr       */
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

	init_interacrive_signal_handlers();
	while (42)
	{
		input = read_command(PROMPT);
		if (input == NULL)
			return (ft_putstr_fd("exit\n", STDOUT_FILENO),
					sh_cleanup(sh, NULL));
		if (!lex_input(input, &sh->lst))
			return (sh_cleanup(sh, input));
		if (!handle_prompt_syntax_errors(sh, input))
			continue ;
		sh->last_status = set_or_get_exit_status(GET, -1);
		if (!expand_tokens(sh, &sh->lst))
			return (sh_cleanup(sh, input));
		if (!command_table(sh))
			return (sh_cleanup(sh, input));
		if (sh->cmd_tab[0][0])
			execute(*sh);
		sh_cleanup(sh, input);
	}
}
