/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:02:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/27 13:23:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_ht_item
{
    char	*key;
    char	*value;
	int		is_deleted;
}				t_ht_item;

typedef struct	s_ht_table
{
    int			base_size;
    int			size;
    int			count;
    t_ht_item	**items;
}				t_ht_table;

int				next_prime(int n);
int				ft_pow(int nb, int power);

t_ht_table	*ht_new(void);
void		ht_table_free(t_ht_table *ht);
void		ht_set(t_ht_table *ht, const char *key, const char *value);
void		ht_delete(t_ht_table *ht, const char *key);
char		*ht_get(t_ht_table *ht, const char *key);

#define HT_PRIME_1 233
#define HT_PRIME_2 239
#define HT_INITIAL_BASE_SIZE 53
