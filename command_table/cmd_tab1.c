/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:39:35 by omougel           #+#    #+#             */
/*   Updated: 2024/06/01 23:40:28 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command_table.h"

size_t	count_redir(t_token *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		if (isredir(*lst))
			count++;
		lst = lst->next;
	}
	return (count);
}

size_t	malloc_size(t_token *lst)
{
	size_t	size;

	size = count_pipe(lst) * 2 + count_redir(lst) + 1;
	return (size);
}

t_token	*find_redir(t_token **lst)
{
	while (*lst && (*lst)->op_type != PIPE)
	{
		if (isredir(**lst))
			return (*lst);
		*lst = (*lst)->next;
	}
	return (NULL);
}

t_token	*jump_redir(t_token *lst)
{
	return (lst->next->next);
}

size_t	cmd_size(t_token *lst)
{
	size_t	size;

	size = 0;
	while (lst && lst->op_type != PIPE)
	{
		if (isredir(*lst))
			lst = jump_redir(lst);
		else
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}
