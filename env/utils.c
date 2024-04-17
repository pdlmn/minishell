/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:36:24 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/17 14:37:19 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"

char	*ft_strjoin_delim(char *s1, char *s2, char delim)
{
	size_t	l1;
	size_t	l2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (l1 + l2 + 2));
	if (!str)
		return (0);
	ft_memcpy(str, s1, l1);
	str[l1++] = delim;
	ft_memcpy(&str[l1], s2, l2);
	str[l1 + l2] = '\0';
	return (str);
}
