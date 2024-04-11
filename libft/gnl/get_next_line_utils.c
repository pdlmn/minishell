/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:29:00 by omougel           #+#    #+#             */
/*   Updated: 2024/04/08 23:00:06 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

void	ft_strncpy(char *src, char *dest, int size)
{
	int	i;

	i = 0;
	while (i + 1 < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strnewcat(char *src1, char *src2)
{
	char	*dest;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	if (!src2)
		return (src1);
	dest = malloc((ft_strlen(src1) + ft_strlen(src2) + 1) * sizeof(char));
	if (!dest)
	{
		free(src1);
		free(src2);
		return (NULL);
	}
	while (src1[i1])
	{
		dest[i1] = src1[i1];
		i1++;
	}
	while (src2[i2])
		dest[i1++] = src2[i2++];
	dest[i1] = '\0';
	free(src1);
	free(src2);
	return (dest);
}

int	ft_strnchr(const char *str, int len)
{
	int	i;

	i = 0;
	while (i < len && str[i])
		if (str[i++] == '\n')
			return (1);
	return (0);
}

int	ft_malloc_len(char c, int i, int previous)
{
	if (c == '\n')
		return (i - previous + 2);
	return (i - previous + 1);
}
