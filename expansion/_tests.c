/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/03 02:51:20 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

int	main(void)
{
	t_ht_table	*ht;

	ht = ht_new(100);
	ht_set(ht, "ASD", "123");
	char *test1 = ft_strdup("$ASD");      // 123
	char *test2 = ft_strdup("Hello$ASD"); // Hello123
	char *test3 = ft_strdup("$ASDHello"); // {empty}
	char *test4 = ft_strdup("$ASD$ASD");  // 123123
	char *test5 = ft_strdup("$1");        // {empty}
	char *test6 = ft_strdup("$123");      // 23
	char *test7 = ft_strdup("\"$ASD\"");  // 123

	char *res1 = expand_word(ht, test1);
	char *res2 = expand_word(ht, test2);
	char *res3 = expand_word(ht, test3);
	char *res4 = expand_word(ht, test4);
	char *res5 = expand_word(ht, test5);
	char *res6 = expand_word(ht, test6);
	char *res7 = expand_word(ht, test7);

	printf("%s\n", res1);
	printf("%s\n", res2);
	printf("%s\n", res3);
	printf("%s\n", res4);
	printf("%s\n", res5);
	printf("%s\n", res6);
	printf("%s\n", res7);

	free(test1);
	free(test2);
	free(test3);
	free(test4);
	free(test5);
	free(test6);
	free(test7);

	free(res1);
	free(res2);
	free(res3);
	free(res4);
	free(res5);
	free(res6);
	free(res7);

	ht_table_free(ht);
}
