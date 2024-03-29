/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:49:14 by omougel           #+#    #+#             */
/*   Updated: 2024/03/29 12:33:34 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int	is_input(char *redir)
{
	if (!ft_strcmp(redir, "<") || !ft_strcmp(redir, "<<"))
		return (1);
	return (0);
}

int	is_output(char *redir)
{
	if (!ft_strcmp(redir, ">") || !ft_strcmp(redir, ">>"))
		return (1);
	return (0);
}

char **creat_builtins(void)
{
	char *builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	return (builtins);
}

int	is_builtin(char *cmd)
{
	char	**builtins;
	int		i;

	builtins = creat_builtins();
	i = 0;
	while (builtins[i])
		if (!ft_strcmp(cmd, builtins[i++]))
			return (1);
	return (0);
}

int	is_there_pipe(char ***cmd_tab)
{
	size_t	i;

	i = 0;
	while (cmd_tab && cmd_tab[i])
	{
		if (!ft_strcmp("|", cmd_tab[i][0]))
			return (1);
		i++;
	}
	return (0);
}

int	here_doc(char *lim)
{
	char	*buffer;
	int		fd[2];

	buffer = get_next_line(STDIN_FILENO);
	if (pipe(fd) == -1)
		return (ERROR); //TODO
	while(buffer && ft_strcmp(buffer, lim))
	{
		write(fd[1], buffer, ft_strlen(buffer)); //deal with error case maybe
		free(buffer);
		buffer = get_next_line(STDIN_FILENO);
	}
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

void	execution(char ***cmd_tab)
{

}
