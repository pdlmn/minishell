/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:47:26 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/12 10:37:01 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = malloc(l1 + l2 + 1);
	if (!str)
		return (0);
	ft_memcpy(str, s1, l1);
	ft_memcpy(&str[l1], s2, l2);
	str[l1 + l2] = '\0';
	return (str);
}
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = '/';
	while (s2 && s2[i - 1 - ft_strlen(s1)])
	{
		dest[i] = s2[i - 1 - ft_strlen(s1)];
		i++;
	}
	return (dest);
}

