/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:46:59 by omougel           #+#    #+#             */
/*   Updated: 2024/06/09 16:46:52 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command_table.h"

int	isredir(t_token node)
{
	return (node.op_type != PIPE && node.op_type != NOT_OPERATOR);
}

int	is_word(enum e_token type)
{
	return (type == WORD || type == DELIM || type == QDELIM);
}

void	ft_free_table(t_minishell *sh)
{
	size_t	i;
	char	***tab;

	tab = sh->cmd_tab;
	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	sh->cmd_tab = NULL;
}

size_t	count_pipe(t_token *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		if (lst->op_type == PIPE)
			count++;
		lst = lst->next;
	}
	return (count);
}
