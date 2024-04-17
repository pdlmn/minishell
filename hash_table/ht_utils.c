/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:58:08 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/01 03:41:29 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_prime(int n)
{
	long	i;

	if (n < 2)
		return (0);
	if (n == 2 || n == 3)
		return (1);
	if (n % 2 == 0)
		return (0);
	i = 3;
	while (i * i <= n)
	{
		if (n % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

int	next_prime(int n)
{
	if (n <= 2)
		return (2);
	if (n % 2 == 0)
		n++;
	while (!is_prime(n))
		n += 2;
	return (n);
}
