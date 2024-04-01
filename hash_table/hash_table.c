/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:28:10 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/01 03:45:19 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_table.h"

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

static void	ht_transfer_stats(t_ht_table *ht, t_ht_table *tmp_ht, int base_size)
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

static void	ht_resize(t_ht_table *ht, int base_size)
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

static t_ht_item	*ht_new_item(const char *k, const char *v)
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

static inline void	ht_item_free(t_ht_item *i)
{
	if (!i)
		return ;
	free(i->key);
	free(i->value);
	free(i);
}

static unsigned long	ht_hash(const char *key)
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

static int	ht_find_index(t_ht_table *ht, const char *key)
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
	return (item);
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

void	ht_table_free(t_ht_table *ht)
{
	int	i;

	i = 0;
	while (i < ht->size)
	{
		if (ht->items[i])
			ht_item_free(ht->items[i]);
		i++;
	}
	free(ht->items);
	free(ht);
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
