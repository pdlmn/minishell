/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:03:14 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 02:19:46 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command_table.h"

t_token	*fill_cmd(t_token *lst, char ***cmd_tab)
{
	size_t	i;

	i = 0;
	*cmd_tab = ft_calloc(cmd_size(lst) + 1, sizeof(char *));
	if (!cmd_tab)
		return (lst);
	while (lst && lst->op_type != PIPE)
	{
		if (isredir(*lst))
			lst = jump_redir(lst);
		else
		{
			(*cmd_tab)[i++] = lst->content;
			lst = lst->next;
		}
	}
	(*cmd_tab)[i] = NULL;
	return (lst);
}

int	alloc_size(t_token *lst)
{
	int	size;

	size = 2;
	if (isredir(*lst) && is_word(lst->next->type))
		size++;
	if (lst->op_type == HEREDOC && lst->next->type == QDELIM)
		size++;
	return (size);
}

t_token	*fill_operator(t_token *lst, char ***cmd_tab)
{
	size_t	i;

	i = 0;
	*cmd_tab = ft_calloc(alloc_size(lst), sizeof(char *));
	if (!*cmd_tab)
		return (lst);
	(*cmd_tab)[i++] = lst->content;
	if (isredir(*lst) && is_word(lst->next->type))
	{
		lst = lst->next;
		(*cmd_tab)[i++] = lst->content;
		if (lst->type == QDELIM)
			(*cmd_tab)[i++] = "1";
	}
	(*cmd_tab)[i] = NULL;
	return (lst->next);
}

t_token	*fill_line(t_token *lst, char ***cmd_tab, size_t *i)
{
	t_token	*tmp;

	if (lst && lst->type == OPERATOR)
		return (fill_operator(lst, &cmd_tab[*i]));
	tmp = lst;
	while (find_redir(&tmp))
	{
		tmp = fill_line(tmp, cmd_tab, i);
		if (!cmd_tab[*i])
			return (lst);
		(*i)++;
	}
	return (fill_cmd(lst, &cmd_tab[*i]));
}
