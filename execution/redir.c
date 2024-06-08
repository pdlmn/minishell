/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:00:55 by omougel           #+#    #+#             */
/*   Updated: 2024/06/08 22:22:17 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	here_doc(char *lim, char *quoted)
{
	char	*old_buff;
	char	*buff;
	char	*new_line;
	int		fd[2];

	init_heredoc_signal_handlers();
	write(1, "> ", 2);
	buff = get_next_line(0);
	if (buff)
	{
		new_line = ft_strchr(buff, '\n');
		if (new_line)
		*new_line = '\0';
	}
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	while (buff && ft_strcmp(buff, lim))
	{
		if (!quoted)
		{
			old_buff = buff;
			buff = expend_heredoc(buff);
			free(old_buff);
		}
		write(fd[1], buff, ft_strlen(buff));
		write(fd[1], "\n", 1);
		free(buff);
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (buff)
		{
			new_line = ft_strchr(buff, '\n');
			if (new_line)
				*new_line = '\0';
		}
		if (set_or_get_exit_status(GET, -1) == 130)
			break;
	}
	free(buff);
	close(fd[1]);
	if (set_or_get_exit_status(GET, -1) == 130)
		return (get_next_line(-1), -1);
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
