#include "../include/hash_table.h"

static t_ht_table	*ht_new_sized(const int base_size)
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

static void	ht_resize(t_ht_table *ht, int base_size)
{
	t_ht_table	*new_ht;
	int			i;
	t_ht_item	*item;
	int			tmp_size;
	t_ht_item	**tmp_items;

	if (ht->base_size < HT_INITIAL_BASE_SIZE)
		return ;
	new_ht = ht_new_sized(base_size);
	i = 0;
	while (i < ht->size)
	{
		item = ht->items[i];
		if (item != 0 && !item->is_deleted)
			ht_set(new_ht, item->key, item->value);
		else if (item->is_deleted)
			free(item);
	}
	ht->base_size = base_size;
	ht->count = new_ht->count;
	tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;
	tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;
	ht_table_free(new_ht);
}

static void	ht_resize_up(t_ht_table *ht)
{
	ht_resize(ht, ht->base_size * 2);
}

static void	ht_resize_down(t_ht_table *ht)
{
	ht_resize(ht, ht->base_size / 2);
}

static t_ht_item	*ht_new_item(const char *k, const char *v)
{
	t_ht_item	*item;

	item = malloc(sizeof(t_ht_item));
	if (!item)
		return (NULL);
	item->key = ft_strdup(k);
	item->value = ft_strdup(v);
	return (item);
}

t_ht_table	*ht_new(void)
{
	return (ht_new_sized(HT_INITIAL_BASE_SIZE));
}

static void	ht_item_free(t_ht_item *i)
{
	free(i->key);
	free(i->value);
	free(i);
}

/* Partial freeing of the item and setting the deletion flag */
static void	ht_item_delete(t_ht_item *item)
{
	free(item->key);
	free(item->value);
	item->key = NULL;
	item->value = NULL;
	item->is_deleted = 1;
}

void	ht_table_free(t_ht_table *ht)
{
	int			i;
	t_ht_item	*item;

	i = 0;
	while (i < ht->count)
	{
		item = ht->items[i];
		if (item != 0)
			ht_item_free(item);
		i++;
	}
	free(ht->items);
	free(ht);
}

static int	ht_hash(const char *s, const int a, const int buckets)
{
	const int		l = ft_strlen(s);
	unsigned long	hash;
	int				i;

	hash = 0;
	i = 0;
	while (i < l)
	{
		hash += ft_pow(a, (l - (i + 1))) * s[i];
		hash %= buckets;
		i++;
	}
	return ((int)hash);
}

/* hash_b + 1 in case hash_b is 0 */
static int	ht_get_hash(const char *s, const int buckets, const int attempt)
{
	const int	hash_a = ht_hash(s, HT_PRIME_1, buckets);
	const int	hash_b = ht_hash(s, HT_PRIME_2, buckets);

	return (hash_a + (attempt * (hash_b + 1)) % buckets);
}

/* Inserts pair key-valye to hash table, resizes on 70% of load */
void	ht_set(t_ht_table *ht, const char *key, const char *value)
{
	const int	load = (ht->count * 100) / ht->size;
	t_ht_item	*item;
	int			attempt;
	int			index;
	t_ht_item	*curr_item;

	if (load > 70)
		ht_resize_up(ht);
	item = ht_new_item(key, value);
	attempt = 0;
	index = ht_get_hash(key, ht->size, attempt);
	curr_item = ht->items[index];
	while (curr_item != 0 && !curr_item->is_deleted)
	{
		if (ft_strcmp(key, curr_item->key))
		{
			ht_item_free(curr_item);
			ht->items[index] = item;
			return ;
		}
		index = ht_get_hash(item->key, ht->size, ++attempt);
		curr_item = ht->items[index];
	}
	ht->items[index] = item;
	ht->count++;
}

void	ht_delete(t_ht_table *ht, const char *key)
{
	const int	load = (ht->count * 100) / ht->size;
	int			attempt;
	int			index;
	t_ht_item	*item;

	// cuttin the size in two if the table is 10% filled
	// AND if it was resized up at least once
	if (load < 10)
		ht_resize_down(ht);
	attempt = 0;
	index = ht_get_hash(key, ht->size, attempt);
	item = ht->items[index];
	while (item != 0)
	{
		if (!item->is_deleted && ft_strcmp(key, item->key) == 0)
		{
			ht_item_delete(item);
			ht->count--;
		}
		index = ht_get_hash(key, ht->size, ++attempt);
		item = ht->items[index];
	}
}

char	*ht_get(t_ht_table *ht, const char *key)
{
	int			attempt;
	int			index;
	t_ht_item	*item;

	attempt = 0;
	index = ht_get_hash(key, ht->size, attempt);
	item = ht->items[index];
	while (item != 0)
	{
		if (ft_strcmp(key, item->key) == 0 && !item->is_deleted)
			return (item->value);
		index = ht_get_hash(key, ht->size, ++attempt);
		item = ht->items[index];
	}
	return (0);
}
