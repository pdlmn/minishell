/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:45:20 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/17 16:49:30 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_command(char *prompt)
{
	char	*command;

	command = readline(prompt);
	if (!command)
		return (NULL);
	add_history(command);
	return (command);
}

int	main(int argc, char **argv, char **env)
{
	static t_minishell	sh;
	char				*input;

	(void)argc;
	(void)argv;
	env_init(env, &sh);
	while (1)
	{
		input = read_command("-> ");
		if (input == NULL)
			return (EXIT_FAILURE);
		if (!lexer(input, &sh))
			return (free(input), EXIT_FAILURE);
		expansion(&sh);
		token_list_print(&sh.lst);
		token_list_free(&sh.lst);
		free(input);
	}
	rl_clear_history();
}
