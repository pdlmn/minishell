/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:28:10 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/09 17:01:26 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_table.h"

char	*ht_get(t_ht_table *ht, const char *key)
{
	const int		index = ht_find_index(ht, key);
	const t_ht_item	*item = ht->items[index];

	if (!item)
		return (NULL);
	return (item->value);
}

/* Inserts pair key-valye to hash table, resizes on 70% of load */
t_ht_item	*ht_set(t_ht_table *ht, const char *key, const char *value)
{
	const int	load = (ht->count * 100) / ht->size;
	int			index;
	t_ht_item	*item;

	if (load > 70)
		ht_resize(ht, ht->base_size * 2);
	index = ht_find_index(ht, key);
	item = ht->items[index];
	if (item)
	{
		free(item->value);
		item->value = ft_strdup(value);
		if (!item->value)
			return (NULL);
		return (item);
	}
	ht->items[index] = ht_new_item(key, value);
	if (!ht->items[index])
		return (NULL);
	ht->count++;
	return (ht->items[index]);
}

void	ht_delete(t_ht_table *ht, const char *key)
{
	const int	index = ht_find_index(ht, key);
	t_ht_item	*item;

	item = ht->items[index];
	if (!item)
		return ;
	free(item->key);
	free(item->value);
	item->key = NULL;
	item->value = NULL;
	item->is_deleted = 1;
}

void	ht_free_table(t_ht_table **ht_ptr)
{
	int			i;
	t_ht_table	*ht;

	if (*ht_ptr == NULL)
		return;
	i = 0;
	ht = *ht_ptr;
	while (i < ht->size)
	{
		if (ht->items[i])
			ht_item_free(ht->items[i]);
		i++;
	}
	free(ht->items);
	free(ht);
	*ht_ptr = NULL;
}

t_ht_table	*ht_new(int base_size)
{
	t_ht_table	*ht;

	ht = malloc(sizeof(t_ht_table));
	if (!ht)
		return (NULL);
	ht->base_size = base_size;
	ht->size = next_prime(base_size);
	ht->count = 0;
	ht->items = ft_calloc(ht->size, sizeof(t_ht_item *));
	if (!ht->items)
		return (NULL);
	return (ht);
}
