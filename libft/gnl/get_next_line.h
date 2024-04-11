/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:28:47 by omougel           #+#    #+#             */
/*   Updated: 2024/04/08 23:00:44 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	ft_strncpy(char *src, char *dest, int size);
char	*ft_strnewcat(char *src1, char *src2);
char	*get_next_line(int fd);
int		ft_strnchr(const char *str, int len);
int		ft_malloc_len(char c, int i, int previous);

#endif
