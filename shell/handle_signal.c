/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:35:45 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/05 23:53:50 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_signal(int signal, siginfo_t *siginfo, void *context)
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
