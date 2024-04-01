/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:02:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/01 04:04:17 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				next_prime(int n);

void			ht_transfer_stats(t_ht_table *ht, t_ht_table *tmp_ht,
					int base_size);
void			ht_resize(t_ht_table *ht, int base_size);
t_ht_item		*ht_new_item(const char *k, const char *v);
void			ht_resize(t_ht_table *ht, int base_size);
void			ht_item_free(t_ht_item *i);
unsigned long	ht_hash(const char *key);
int				ht_find_index(t_ht_table *ht, const char *key);

#define FNV_OFFSET 2166136261u
#define FNV_PRIME 16777619u
#define HT_INITIAL_BASE_SIZE 113
