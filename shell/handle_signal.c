/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:35:45 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/06 18:13:02 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/ioctl.h>

void	exec_handle_signal(int signal)
{
    (void)signal;
}

void	parsing_handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	init_signals(struct sigaction	*sa_sigint)
{
	sa_sigint->sa_handler = &exec_handle_signal;
	sa_sigint->sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&(sa_sigint)->sa_mask);
	sigaction(SIGINT, sa_sigint, NULL);
}

void init_exec_signals() {
    struct sigaction sa_sigint;

    ft_bzero(&sa_sigint, sizeof(sa_sigint));
    sigemptyset(&(sa_sigint).sa_mask);
    sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
    sa_sigint.sa_handler = exec_handle_signal;
    sigaction(SIGINT, &sa_sigint, NULL);
    sigaction(SIGQUIT, &sa_sigint, NULL);
}
