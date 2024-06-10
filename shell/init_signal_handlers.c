/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:34:47 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 10:35:09 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_interacrive_signal_handlers(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_handler = &interactive_signal_handler;
	sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&(sa_sigint).sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	init_exec_signal_handlers(void)
{
	struct sigaction	sa_sigint;

	ft_bzero(&sa_sigint, sizeof(sa_sigint));
	sigemptyset(&(sa_sigint).sa_mask);
	sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	sa_sigint.sa_handler = exec_signal_handler;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigint, NULL);
	signal(SIGTSTP, SIG_IGN);
}

void	init_heredoc_signal_handlers(void)
{
	struct sigaction	sa_sigint;

	ft_bzero(&sa_sigint, sizeof(sa_sigint));
	sigemptyset(&(sa_sigint).sa_mask);
	sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	sa_sigint.sa_handler = heredoc_signal_handler;
	sigaction(SIGINT, &sa_sigint, NULL);
}
