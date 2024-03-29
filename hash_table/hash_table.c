#include "../include/hash_table.h"

// env ->  ht_table
// ht_get("HOME") -> /home/emuminov
// char *input -> lst<t_token> -> (verification of syntax) -> char ***command_table -> char ***command_table -> execution
// lexer -> parser -> expansion
// { "cat", "$FILE" } -> { "cat, "example.txt" }

// TODO: ht_table -> command_table

static t_ht_table	*ht_new_sized(int base_size)
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
	t_ht_table	*tmp_ht;
	t_ht_item	**tmp_items;
	int			tmp_size;
	int			i;

	if (ht->base_size < HT_INITIAL_BASE_SIZE)
		return ;
	tmp_ht = ht_new_sized(base_size);
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
	ht->base_size = base_size;
	tmp_size = ht->size;
	ht->size = tmp_ht->size;
	tmp_items = ht->items;
	ht->items = tmp_ht->items;
	tmp_ht->items = tmp_items;
	tmp_ht->size = tmp_size;
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
	// todo handle memory error
	item->is_deleted = 0;
	return (item);
}

static void	ht_item_free(t_ht_item *i)
{
	if (!i)
		return ;
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

	// NOTE: if (hash_b + 1) % buckets == 0, index will always be just hash_a
	return ((hash_a + (attempt * (hash_b + 1))) % buckets);
}

t_ht_table	*ht_new(void)
{
	return (ht_new_sized(HT_INITIAL_BASE_SIZE));
}

char	*ht_get(t_ht_table *ht, const char *key)
{
	int			attempt;
	int			index;
	t_ht_item	*item;

	attempt = 0;
	index = ht_get_hash(key, ht->size, attempt);
	item = ht->items[index];
	while (item != NULL)
	{
		if (ft_strcmp(key, item->key) == 0 && !item->is_deleted)
			return (item->value);
		index = ht_get_hash(key, ht->size, ++attempt);
		item = ht->items[index];
	}
	return (NULL);
}

/* Inserts pair key-valye to hash table, resizes on 70% of load */
void	ht_set(t_ht_table *ht, const char *key, const char *value)
{
	// const int	load = (ht->count * 100) / ht->size;
	t_ht_item	*item;
	t_ht_item	*curr_item;
	int			attempt;
	int			index;

	// if (load > 70)
	// {
	// 	ft_printf("ENTERING RESIZING!\n");
	// 	ht_resize(ht, ht->base_size * 2);
	// }
	item = ht_new_item(key, value);
	attempt = 0;
	index = ht_get_hash(key, ht->size, attempt);
	curr_item = ht->items[index];
	while (curr_item != NULL && !curr_item->is_deleted)
	{
		if (ft_strcmp(key, curr_item->key) == 0)
		{
			ft_printf("key: %s\n", item->key);
			ft_printf("index: %d\n", index);
			ht_item_free(curr_item);
			ht->items[index] = item;
			return ;
		}
		ft_printf("key: %s\n", item->key);
		ft_printf("current index: %d\n", index);
		index = ht_get_hash(item->key, ht->size, ++attempt);
		curr_item = ht->items[index];
	}
	ft_printf("key: %s\n", item->key);
	ft_printf("final index: %d\n", index);
	ft_printf("=============\n");
	ht->items[index] = item;
	ht->count++;
}

void	ht_delete(t_ht_table *ht, const char *key)
{
	const int	load = (ht->count * 100) / ht->size;
	int			attempt;
	int			index;
	t_ht_item	*item;

	if (load < 10)
		ht_resize(ht, ht->base_size / 2);
	attempt = 0;
	index = ht_get_hash(key, ht->size, attempt);
	item = ht->items[index];
	while (item != NULL)
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

void	ht_table_free(t_ht_table *ht)
{
	int			i;

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

	ft_printf("{\n");
	i = 0;
	while (i < ht->size)
	{
		ft_printf("\t");
		if (!ht->items[i])
			ft_printf("%d NULL\n", i);
		else if (ht->items[i]->is_deleted)
			ft_printf("%d DELETED\n", i);
		else
			ft_printf("%d KEY: %s, VALUE: %s\n", i, ht->items[i]->key, ht->items[i]->value);
		i++;
	}
	ft_printf("}\n");
}
