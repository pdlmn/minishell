/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:35:45 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/07 18:37:02 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/ioctl.h>

void	exec_signal_handler(int signal)
{
    (void)signal;
}

void	heredoc_signal_handler(int signal)
{
	(void)signal;
	set_or_get_exit_status(SET, 130);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	close(0);
}

void	interactive_signal_handler(int signal)
{
	(void)signal;
	set_or_get_exit_status(SET, 130);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	init_interacrive_signal_handlers(void)
{
    struct sigaction sa_sigint;

	sa_sigint.sa_handler = &interactive_signal_handler;
	sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&(sa_sigint).sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void init_exec_signal_handlers(void) {
    struct sigaction sa_sigint;

    ft_bzero(&sa_sigint, sizeof(sa_sigint));
    sigemptyset(&(sa_sigint).sa_mask);
    sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
    sa_sigint.sa_handler = exec_signal_handler;
    sigaction(SIGINT, &sa_sigint, NULL);
    sigaction(SIGQUIT, &sa_sigint, NULL);
}

void init_heredoc_signal_handlers(void) {
    struct sigaction sa_sigint;

    ft_bzero(&sa_sigint, sizeof(sa_sigint));
    sigemptyset(&(sa_sigint).sa_mask);
    sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
    sa_sigint.sa_handler = heredoc_signal_handler;
    sigaction(SIGINT, &sa_sigint, NULL);
}
