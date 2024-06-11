/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:00:55 by omougel           #+#    #+#             */
/*   Updated: 2024/06/11 18:08:07 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include <readline/readline.h>

int	here_doc(char *lim, char *quoted)
{
	char	*buff;
	int		fd[2];
	int		saved_in;

	init_heredoc_signal_handlers();
	saved_in = dup(STDIN_FILENO);
	buff = readline(">");
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	while (buff && ft_strcmp(buff, lim))
	{
		if (!quoted)
			buff = expend_heredoc(buff);
		ft_putstr_fd(buff, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(buff);
		buff = readline(">");
		if (set_or_get_exit_status(GET, -1) == 130)
			break ;
	}
	free(buff);
	close(fd[1]);
	if (set_or_get_exit_status(GET, -1) == 130)
		return (close(fd[0]), dup2(saved_in, STDIN_FILENO), -2);
	return (fd[0]);
}

int	redir_input(char *infile)
{
	return (open(infile, O_RDONLY, 0644));
}

int	redir_output(char *outfile)
{
	return (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	append_output(char *outfile)
{
	return (open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
}
