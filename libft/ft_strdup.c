/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:33:54 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/02 23:22:23 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*str;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	str = malloc(size);
	if (!str)
		return (0);
	ft_memcpy(str, s, size);
	return (str);
}
