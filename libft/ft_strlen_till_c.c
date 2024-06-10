/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_till_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:48:02 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 00:51:00 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_till_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
