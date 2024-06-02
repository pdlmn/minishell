/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:00:55 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 01:01:22 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	here_doc(char *lim, char *quoted)
{
	char	*buffer;
	int		fd[2];

	buffer = readline(">");
	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	while (buffer && ft_strcmp(buffer, lim))
	{
		if (!quoted)
			buffer = expend_heredoc(buffer);
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		free(buffer);
		buffer = readline(">");
	}
	free(buffer);
	close(fd[1]);
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
