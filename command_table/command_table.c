/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:41:59 by omougel           #+#    #+#             */
/*   Updated: 2024/03/22 16:07:58 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

static size_t	isredir(t_token node)
{
	return (node.op_type != PIPE && node.op_type != NOT_OPERATOR);
}

void	ft_free_table(char ***tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

static size_t	count_pipe(t_token *lst)
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

static size_t	count_redir(t_token *lst)
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
/*
char	**fill_line(t_token **lst)
{
	static t_token	*lst_ptr = *lst;

}
*/


t_token	*find_redir(t_token *lst)
{
	while (lst->op_type != PIPE && lst)
	{
		if (isredir(*lst))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_token	*jump_redir(t_token *lst)
{
	lst = lst->next;
	if (lst->type == WORD)
		return (lst->next);
	return (lst);
}

size_t	cmd_size(t_token *lst)
{
	size_t	size;

	size = 0;
	while (lst->op_type != PIPE && lst)
	{
		if (isredir(*lst))
			lst = jump_redir(lst);
		else
			size++;
	}
	return (size);
}

t_token	*fill_cmd(t_token *lst, char ***cmd_tab)
{
	size_t	i;

	i = 0;
	*cmd_tab = ft_calloc(cmd_size(lst) + 1, sizeof(char **));
	if (!cmd_tab)
		return (lst);
	while (lst->op_type != PIPE && lst)
	{
		if (isredir(*lst))
			lst = jump_redir(lst);
		else
		{
			*cmd_tab[i++] = lst->content;
			lst = lst->next;
		}
	}
	return (lst);
}

t_token	*fill_operator(t_token *lst, char ***cmd_tab)
{
	*cmd_tab = ft_calloc(2 + (isredir(*lst) && lst->next->type == WORD), sizeof(char **));
	if (!*cmd_tab)
		return (lst);
	*cmd_tab[0] = lst->content;
	if (lst->next->type == WORD)
	{
		lst = lst->next;
		*cmd_tab[1] = lst->content;
	}
	return (lst->next);
}

t_token	*fill_line(t_token *lst, char ***cmd_tab, size_t *i)
{
	t_token	*tmp;

	if (lst->type == OPERATOR)
		return (fill_operator(lst, &cmd_tab[*i]));
	/*
	if (lst->op_type == PIPE)
	{
		cmd_tab[*i] = ft_calloc(2, sizeof(char **));
		if (!*cmd_tab)
			return (NULL);
		*cmd_tab[0] = lst->content;
		return (lst->next);
	}
	if (isredir(*lst))
	{
		*cmd_tab = ft_calloc(2 + (lst->next->type == WORD), sizeof(char **));
		if (!*cmd_tab)
			return (NULL);
		*cmd_tab[0] = lst->content;
		if (lst->next->type == WORD)
		{
			lst = lst->next;
			*cmd_tab[1] = lst->content;
		}
		return (lst->next);
	}
	*/
	tmp = lst;
	while (find_redir(tmp))
	{
		tmp = fill_line(tmp, cmd_tab, i);
		if (!cmd_tab[*i])
			return (lst);
		(*i)++;
	}
	fill_cmd(lst, &cmd_tab[*i]);
	if (!cmd_tab[*i])
		return (lst);
	return (lst);
}

char	***command_table(t_token **lst)
{
	char	***cmd_tab;
	size_t	tab_size;
	size_t	i;
	t_token	*tmp;
	
	tmp = *lst;
	i = 0;
	tab_size = malloc_size(*lst);
	cmd_tab = ft_calloc(tab_size + 1, sizeof(char **));
	if (!cmd_tab)
		return (NULL);
	while (i < tab_size)
	{
		tmp = fill_line(tmp, cmd_tab, &i);
		if (!cmd_tab[i])
			return (ft_free_table(cmd_tab), NULL);
		i++;
	}
	return (cmd_tab);
}
