/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:35:45 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/11 17:59:55 by emuminov         ###   ########.fr       */
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
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(0);
}

void	interactive_signal_handler(int signal)
{
	(void)signal;
	set_or_get_exit_status(SET, 130);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
