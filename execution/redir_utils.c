/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:01:59 by omougel           #+#    #+#             */
/*   Updated: 2024/06/27 22:30:50 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include <stdlib.h>

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
	if (!res)
		return (NULL);
	i = 0;
	while (curr)
	{
		j = 0;
		while (curr->content[j])
			res[i++] = curr->content[j++];
		if (curr->space_after)
			res[i++] = ' ';
		curr = curr->next;
	}
	res[i] = '\0';
	return (res);
}

char	*parse_unquoted_heredoc_input(t_minishell *msh, char *buffer)
{
	t_minishell	tmp_msh;

	tmp_msh.lst.head = NULL;
	tmp_msh.lst.tail = NULL;
	tmp_msh.env = msh->env;
	if (!lex_heredoc_input(buffer, &tmp_msh.lst, DELIM))
		return (free(buffer), NULL);
	if (!expand_heredoc(&tmp_msh, &tmp_msh.lst, DELIM))
		return (free(buffer), token_list_free(&tmp_msh.lst), NULL);
	free(buffer);
	buffer = join_expanded_strings(&tmp_msh.lst);
	token_list_free(&tmp_msh.lst);
	return (buffer);
}
