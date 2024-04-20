/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:45:20 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/04 17:14:02 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_command(char *prompt)
{
	char	*command;

	command = readline(prompt);
	if (!command) // what does that mean if readline returns NULL ??
		return (NULL);
	add_history(command);
	return (command);
}

int	set_or_get_exit_status(enum e_access_flag flag, int new_status)
{
	static int	last_exit_status;

	if (flag == SET)
		last_exit_status = new_status;
	return (last_exit_status);
}

int	main(int argc, char **argv, char **env)
{
	static t_minishell	sh;
	t_err_src			e;
	char				*input;

	(void)argc;
	(void)argv;
	attach_signal_handlers();
	env_init(env, &sh);
	while (42)
	{
		input = read_command(PROMPT);
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			return (EXIT_SUCCESS);// free environement
		}
		if (!lex_input(input, &sh.lst))
			return (free(input), EXIT_FAILURE); // we also  have to free environement
		printf("Pre-expanded tokens:\n");
		token_list_print(&sh.lst);
		e = check_errors(&sh.lst);
		if (e.code != NO_ERRORS)
		{
			print_error_message(&e);
			token_list_free(&sh.lst);
			free(input);// free 
			continue ;
		}
		sh.last_status = set_or_get_exit_status(GET, -1);// why here ??
		if (!expand_tokens(&sh, &sh.lst))
			return (free(input), token_list_free(&sh.lst), EXIT_FAILURE); // free environement
		if (!command_table(&sh))
			return (free(input), token_list_free(&sh.lst), EXIT_FAILURE);// free environement
		printf("Expanded tokens:\n");
		token_list_print(&sh.lst);
		printf("\nCommand table:\n");
		command_table_print(sh.cmd_tab);
		if (sh.cmd_tab[0][0])
			sh.last_status = set_or_get_exit_status(SET, execute(sh));
		ft_free_table(sh.cmd_tab);
		token_list_free(&sh.lst);
		free(input);
	}
	ht_free_table(sh.env);
	rl_clear_history();
}
