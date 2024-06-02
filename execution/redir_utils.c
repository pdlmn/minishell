/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:01:59 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 01:02:43 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

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
		if (curr->space_after)
			res[i++] = ' ';
		curr = curr->next;
	}
	res[i] = '\0';
	return (res);
}

char	*expend_heredoc(char *buffer)
{
	t_minishell	sh;

	lex_heredoc_input(buffer, &sh.lst, DELIM);
	expand_heredoc(&sh, &sh.lst, DELIM);
	buffer = join_expanded_strings(&sh.lst);
	token_list_free(&sh.lst);
	return (buffer);
}
