/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:55:58 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/01 04:00:44 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_table.h"

void	ht_transfer_stats(t_ht_table *ht, t_ht_table *tmp_ht, int base_size)
{
	t_ht_item	**tmp_items;
	int			tmp_size;

	ht->base_size = base_size;
	tmp_size = ht->size;
	ht->size = tmp_ht->size;
	tmp_items = ht->items;
	ht->items = tmp_ht->items;
	ht->count = tmp_ht->count;
	tmp_ht->items = tmp_items;
	tmp_ht->size = tmp_size;
}

void	ht_resize(t_ht_table *ht, int base_size)
{
	t_ht_table	*tmp_ht;
	int			i;

	if (ht->base_size < HT_INITIAL_BASE_SIZE)
		return ;
	tmp_ht = ht_new(base_size);
	i = 0;
	while (i < ht->size)
	{
		if (!ht->items[i])
			;
		else if (!ht->items[i]->is_deleted)
			ht_set(tmp_ht, ht->items[i]->key, ht->items[i]->value);
		else if (ht->items[i]->is_deleted)
		{
			free(ht->items[i]);
			ht->items[i] = NULL;
		}
		i++;
	}
	ht_transfer_stats(ht, tmp_ht, base_size);
	ht_table_free(tmp_ht);
}

t_ht_item	*ht_new_item(const char *k, const char *v)
{
	t_ht_item	*item;

	item = malloc(sizeof(t_ht_item));
	if (!item)
		return (NULL);
	item->key = ft_strdup(k);
	item->value = ft_strdup(v);
	if (!item->key || !item->value)
	{
		free(item->key);
		free(item->value);
		return (NULL);
	}
	item->is_deleted = 0;
	return (item);
}

inline void	ht_item_free(t_ht_item *i)
{
	if (!i)
		return ;
	free(i->key);
	free(i->value);
	free(i);
}

void	ht_table_print(t_ht_table *ht)
{
	int	i;

	printf("{\n");
	i = 0;
	while (i < ht->size)
	{
		printf("\t");
		if (!ht->items[i])
			printf("%d NULL\n", i);
		else if (ht->items[i]->is_deleted)
			printf("%d DELETED\n", i);
		else
			printf("%d KEY: %s, VALUE: %s\n", i, ht->items[i]->key,
				ht->items[i]->value);
		i++;
	}
	printf("}\n");
	printf("Count: %d\n", ht->count);
}
