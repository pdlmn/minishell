/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/08 18:02:19 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"
#include <assert.h>

// #define test_expansion(ht, str, should_be) \
// { \
// 	char *test = expand_word(ht, str); \
// 	printf("%s\n", test); \
// 	assert(ft_strcmp(test, should_be) == 0); \
// 	free(test); \
// }

int	main(void)
{
	t_ht_table	*ht;

	ht = ht_new(100);
	ht_set(ht, "ASD", "123");
	// test_expansion(ht, "$ASD", "123");
	// test_expansion(ht, "Hello$ASD", "Hello123");
	// test_expansion(ht, "$ASDHello", "");
	// test_expansion(ht, "$ASD$ASD", "123123");
	// test_expansion(ht, "$1", "");
	// test_expansion(ht, "$123a", "23a");
	// test_expansion(ht, "\"$ASD\"", "123");
	// test_expansion(ht, "'$ASD'$ASD", "$ASD123");
	// test_expansion(ht, "$\"A\"SD", "ASD");
	// test_expansion(ht, "$\"ASD\"", "ASD");
	// test_expansion(ht, "\"$A\"SD", "SD");
	// test_expansion(ht, "$", "$");
	char *res1 = expand_dquoted(ht, "\"$ASD\"");
	char *res2 = expand_dquoted(ht, "\"hello$ASD\"");
	char *res3 = expand_dquoted(ht, "\"hello$ASDhello\"");
	char *res4 = expand_dquoted(ht, "\"\"");
	char *res5 = expand_dquoted(ht, "\"$ASD$ASD\"");
	char *res6 = expand_dquoted(ht, "\"Hello\"");
	printf("%s\n", res1);
	printf("%s\n", res2);
	printf("%s\n", res3);
	printf("%s\n", res4);
	printf("%s\n", res5);
	printf("%s\n", res6);
	free(res1);
	free(res2);
	free(res3);
	free(res4);
	free(res5);
	free(res6);
	ht_free_table(ht);
}
