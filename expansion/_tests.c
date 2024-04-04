/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/04 12:36:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

#define test_expansion(ht, str) \
{ \
	char *test = expand_word(ht, str); \
	printf("%s\n", test); \
	free(test); \
}

int	main(void)
{
	t_ht_table	*ht;

	ht = ht_new(100);
	ht_set(ht, "ASD", "123");
	test_expansion(ht, "$ASD");      // 123
	test_expansion(ht, "Hello$ASD"); // Hello123
	test_expansion(ht, "$ASDHello"); // {empty}
	test_expansion(ht, "$ASD$ASD");  // 123123
	test_expansion(ht, "$1");        // {empty}
	test_expansion(ht, "$123a");      // 23a
	test_expansion(ht, "\"$ASD\"");  // 123
	ht_table_free(ht);
}
