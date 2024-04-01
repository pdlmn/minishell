/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:56:43 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/01 04:00:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_table.h"

unsigned long	ht_hash(const char *key)
{
	unsigned long	hash;
	int				i;

	hash = FNV_OFFSET;
	i = 0;
	while (key[i])
	{
		hash ^= (unsigned char)key[i];
		hash *= FNV_PRIME;
		i++;
	}
	return (hash);
}

int	ht_find_index(t_ht_table *ht, const char *key)
{
	const unsigned long	hash = ht_hash(key);
	int					index;
	t_ht_item			*item;

	index = hash % ht->size;
	item = ht->items[index];
	while (item)
	{
		if (!item->is_deleted && ft_strcmp(item->key, key) == 0)
			return (index);
		index = (index + 1) % ht->size;
		item = ht->items[index];
	}
	return (index);
}
