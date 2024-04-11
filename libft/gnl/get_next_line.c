/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:28:58 by omougel           #+#    #+#             */
/*   Updated: 2024/04/08 22:57:52 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_return_string(char *buffer, int *i, int previous)
{
	char	*str;

	while (buffer[*i] && buffer[*i] != '\n')
		*i += 1;
	str = malloc(ft_malloc_len(buffer[*i], *i, previous) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strncpy(&buffer[previous], str, ft_malloc_len(buffer[*i], *i, previous));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = "\0";
	char		*return_string;
	static int	error = 1;
	static int	i = 0;
	static int	previous = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[i] == '\0')
	{
		i = 0;
		while (i < BUFFER_SIZE)
			buffer[i++] = '\0';
		error = read(fd, buffer, BUFFER_SIZE);
		i = 0;
		previous = 0;
	}
	if (error == 0 || error == -1)
		return (NULL);
	return_string = ft_return_string(buffer, &i, previous);
	if (buffer[i] == '\n')
		previous = ++i;
	else if (buffer[i] != '\n' && error)
		return_string = ft_strnewcat(return_string, get_next_line(fd));
	return (return_string);
}
