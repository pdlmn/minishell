/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/15 20:29:09 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"
#include <assert.h>

int	calculate_token_list_len(t_tlist *lst)
{
	t_token	*curr;
	int		res;

	curr = lst->head;
	res = 0;
	while (curr)
	{
		res += curr->len;
		res += curr->space_after;
		curr = curr->next;
	}
	return (res);
}

char	*join_expanded_strings(t_tlist *lst)
{
	t_token	*curr;
	char	*res;
	int		len;
	int		i;
	int		j;

	curr = lst->head;
	len = calculate_token_list_len(lst);
	res = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (curr)
	{
		j = 0;
		while (curr->content[j])
			res[i++] = curr->content[j++];
		if (curr->space_after && curr->is_quoted == NOT_QUOTED)
			res[i++] = ' ';
		curr = curr->next;
	}
	res[i] = '\0';
	return (res);
}

void	test_expansion(t_ht_table *ht, char *str, char *should_be)
{
	char	*joined_tokens;
	t_tlist	*lst;

	lst = lexer(str);
	expansion(lst, ht);
	joined_tokens = join_expanded_strings(lst);
	printf("Input:     %s\n", str);
	printf("Should be: %s\n", should_be);
	printf("Result:    %s\n", joined_tokens);
	token_list_print(lst);
	printf("\n");
	assert(ft_strcmp(joined_tokens, should_be) == 0);
	token_list_free(lst);
	free(joined_tokens);
}

int	main(int argc, char **argv, char **env)
{
	t_ht_table	*ht;

	(void)argc;
	(void)argv;
	ht = env_init(env);
	ht_set(ht, "ASD", "123");
	ht_set(ht, "__", "heh");
	ht_set(ht, "HOME", "/home/emuminov");
	test_expansion(ht, "$ASD", "123");
	test_expansion(ht, "Hello$ASD", "Hello123");
	test_expansion(ht, "$ASDHello", "");
	test_expansion(ht, "$\"\"", "");
	test_expansion(ht, "$\"\"\"\"ASD", "ASD");
	test_expansion(ht, "$\"\"\"ASD\"", "ASD");
	test_expansion(ht, "Hello$", "Hello$");
	test_expansion(ht, "\"Hello$\"", "Hello$");
	test_expansion(ht, "\"$ASD\"", "123");
	test_expansion(ht, "$ASD$ASD", "123123");
	test_expansion(ht, "$", "$");
	test_expansion(ht, "\"$ \"", "$ ");
	test_expansion(ht, "\"$' '\"", "$' '");
	test_expansion(ht, "\"$>\"", "$>");
	test_expansion(ht, "\"$a>\"", ">");
	test_expansion(ht, "\"$asd123$%     $  >\"", "$%     $  >");
	test_expansion(ht, "\"$__>\"", "heh>");
	test_expansion(ht, "\"$a1>\"", ">");
	test_expansion(ht, "\"$'$a'1>\"", "$''1>");
	test_expansion(ht, "\"$+''1$>\"", "$+''1$>");
	test_expansion(ht, "\"$^''1$>\"", "$^''1$>");
	test_expansion(ht, "'$ASD'$ASD", "$ASD123");
	test_expansion(ht, "$\"A\"SD", "ASD");
	test_expansion(ht, "$\"ASD\"", "ASD");
	test_expansion(ht, "\"$A\"SD", "SD");
	test_expansion(ht, "$1", "");
	test_expansion(ht, "$123a", "23a");
	test_expansion(ht, "$ asd", "$ asd");
	test_expansion(ht, "$        asd", "$ asd");
	test_expansion(ht, "\"$        asd\"", "$        asd");
	test_expansion(ht, "~/projects", "/home/emuminov/projects");
	// test_expansion(ht, "\"$?'$a'1>\"", "0''1>");
	ht_free_table(ht);
}
