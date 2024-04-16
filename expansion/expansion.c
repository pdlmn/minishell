/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/16 14:59:46 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

t_tlist	*expansion(t_tlist *lst, t_ht_table *ht)
{
	if (!expand_variables(lst, ht))
		return (NULL);
	if (!expand_quotes(lst))
		return (NULL);
	if (!remove_quotes(lst))
		return (NULL);
	if (!join_unspaced_words(lst))
		return (NULL);
	return (lst);
}
