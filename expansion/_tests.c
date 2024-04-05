/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/05 19:53:13 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"
#include <assert.h>

#define test_expansion(ht, str, should_be) \
{ \
	char *test = expand_word(ht, str); \
	printf("%s\n", test); \
	assert(ft_strcmp(test, should_be) == 0); \
	free(test); \
}

int	main(void)
{
	t_ht_table	*ht;

	ht = ht_new(100);
	ht_set(ht, "ASD", "123");
	test_expansion(ht, "$ASD", "123");
	test_expansion(ht, "Hello$ASD", "Hello123");
	test_expansion(ht, "$ASDHello", "");
	test_expansion(ht, "$ASD$ASD", "123123");
	test_expansion(ht, "$1", "");
	test_expansion(ht, "$123a", "23a");
	test_expansion(ht, "\"$ASD\"", "123");
	test_expansion(ht, "'$ASD'$ASD", "$ASD123");
	test_expansion(ht, "$\"A\"SD", "ASD");
	test_expansion(ht, "$\"ASD\"", "ASD");
	test_expansion(ht, "\"$A\"SD", "SD");
	test_expansion(ht, "$", "$");
	ht_free_table(ht);
}
