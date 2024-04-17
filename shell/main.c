/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:45:20 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/17 20:49:48 by emuminov         ###   ########.fr       */
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

enum e_access_flag
{
	SET,
	GET,
};

int	set_or_get_exit_status(enum e_access_flag flag, int new_status)
{
	static int	last_exit_status;

	if (flag == SET)
		last_exit_status = new_status;
	return (last_exit_status);
}

void	handle_signal(int signal, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	if (signal == SIGINT)
	{
		set_or_get_exit_status(SET, 130);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	attach_signal_handlers()
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_sigaction = handle_signal;
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, 0);
	sigaction(SIGQUIT, &sa_sigquit, 0);
}

int	main(int argc, char **argv, char **env)
{
	static t_minishell	sh;
	char				*input;

	(void)argc;
	(void)argv;
	attach_signal_handlers();
	env_init(env, &sh);
	while (1)
	{
		input = read_command(PROMPT);
		if (input == NULL)
			return (EXIT_FAILURE);
		if (!lexer(input, &sh))
			return (free(input), EXIT_FAILURE);
		sh.last_status = set_or_get_exit_status(GET, -1);
		expansion(&sh);
		token_list_print(&sh.lst);
		token_list_free(&sh.lst);
		free(input);
	}
	rl_clear_history();
}
