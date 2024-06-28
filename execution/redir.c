/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:00:55 by omougel           #+#    #+#             */
/*   Updated: 2024/06/28 17:48:46 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include <readline/readline.h>

void	init_heredoc(void)
{
	set_or_get_exit_status(SET, 0);
	init_heredoc_signal_handlers();
}

int	here_doc(t_minishell *msh, char *lim, char *quoted)
{
	char	*buff;
	int		fd[2];
	int		sav_in;

	init_heredoc();
	sav_in = dup(STDIN_FILENO);
	buff = readline(">");
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	while (buff && ft_strcmp(buff, lim))
	{
		if (!quoted)
			buff = parse_unquoted_heredoc_input(msh, buff);
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
		return (close(fd[0]), dup2(sav_in, STDIN_FILENO), close(sav_in), -2);
	return (close(sav_in), fd[0]);
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
