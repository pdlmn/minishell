/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/18 20:56:45 by emuminov         ###   ########.fr       */
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

void	test_expansion(t_minishell *sh, char *str, char *should_be)
{
	char	*joined_tokens;

	lexer(str, sh);
	expansion(sh);
	joined_tokens = join_expanded_strings(&sh->lst);
	printf("Input:     %s\n", str);
	printf("Should be: %s\n", should_be);
	printf("Result:    %s\n", joined_tokens);
	token_list_print(&sh->lst);
	printf("\n");
	assert(ft_strcmp(joined_tokens, should_be) == 0);
	token_list_free(&sh->lst);
	free(joined_tokens);
}

int	main(int argc, char **argv, char **env)
{
	static t_minishell sh;

	(void)argc;
	(void)argv;
	env_init(env, &sh);
	ht_set(sh.env, "ASD", "123");
	ht_set(sh.env, "__", "heh");
	ht_set(sh.env, "HOME", "/home/emuminov");
	test_expansion(&sh, "$ASD", "123");
	test_expansion(&sh, "Hello$ASD", "Hello123");
	test_expansion(&sh, "$ASDHello", "");
	test_expansion(&sh, "$\"\"", "");
	test_expansion(&sh, "$\"\"\"\"ASD", "ASD");
	test_expansion(&sh, "$\"\"\"ASD\"", "ASD");
	test_expansion(&sh, "Hello$", "Hello$");
	test_expansion(&sh, "\"Hello$\"", "Hello$");
	test_expansion(&sh, "\"$ASD\"", "123");
	test_expansion(&sh, "$ASD$ASD", "123123");
	test_expansion(&sh, "$", "$");
	test_expansion(&sh, "\"$ \"", "$ ");
	test_expansion(&sh, "\"$' '\"", "$' '");
	test_expansion(&sh, "\"$>\"", "$>");
	test_expansion(&sh, "\"$a>\"", ">");
	test_expansion(&sh, "\"$asd123$%     $  >\"", "$%     $  >");
	test_expansion(&sh, "\"$__>\"", "heh>");
	test_expansion(&sh, "\"$a1>\"", ">");
	test_expansion(&sh, "\"$'$a'1>\"", "$''1>");
	test_expansion(&sh, "\"$+''1$>\"", "$+''1$>");
	test_expansion(&sh, "\"$^''1$>\"", "$^''1$>");
	test_expansion(&sh, "'$ASD'$ASD", "$ASD123");
	test_expansion(&sh, "$\"A\"SD", "ASD");
	test_expansion(&sh, "$\"ASD\"", "ASD");
	test_expansion(&sh, "\"$A\"SD", "SD");
	test_expansion(&sh, "$1", "");
	test_expansion(&sh, "$123a", "23a");
	test_expansion(&sh, "$ asd", "$ asd");
	test_expansion(&sh, "$        asd", "$ asd");
	test_expansion(&sh, "\"$        asd\"", "$        asd");
	test_expansion(&sh, "\"$?'$a'1>\"", "0''1>");
	test_expansion(&sh, "asd%$%%", "asd%$%%");
	test_expansion(&sh, "~/projects", "/home/emuminov/projects");

	test_expansion(&sh, "cat << $HOME", "cat << $HOME");
	test_expansion(&sh, "cat << $HOME\"\"", "cat << $HOME");
	test_expansion(&sh, "cat << \"\"", "cat << ");
	test_expansion(&sh, "<< $HOME cat", "<< $HOME cat");
	test_expansion(&sh, "<< \"\"$HOME cat", "<< $HOME cat");
	ht_free_table(sh.env);
}
