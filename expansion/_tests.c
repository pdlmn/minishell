/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 17:00:43 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"
#include <assert.h>

void test_expansion(t_ht_table *ht, char *str, char *should_be)
{
	t_tlist *lst = lexer(str);
	expansion(lst, ht);
	printf("%s\n", lst->head->content);
	assert(ft_strcmp(lst->head->content, should_be) == 0);
	token_list_free(lst);
}

int	main(void)
{
	t_ht_table	*ht;

	ht = ht_new(100);
	ht_set(ht, "ASD", "123");
	test_expansion(ht, "$ASD", "123");
	test_expansion(ht, "Hello$ASD", "Hello123");
	test_expansion(ht, "$\"\"", "");
	test_expansion(ht, "$\"\"\"\"ASD", "ASD");
	// test_expansion(ht, "$\"\"\"ASD\"", "ASD");
	// test_expansion(ht, "Hello$", "Hello$");
	// test_expansion(ht, "\"Hello$\"", "Hello$");
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
	// test_expansion(ht, "$ ", "$ ");
	// test_expansion(ht, "$ asd", "$ asd");
	ht_free_table(ht);
}
