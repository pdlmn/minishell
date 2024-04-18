/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:41:59 by omougel           #+#    #+#             */
/*   Updated: 2024/04/18 17:47:37 by emuminov         ###   ########.fr       */
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
	lst = lst->next;
	if (lst->type == WORD)
		return (lst->next);
	return (lst);
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
			size++;
		lst = lst->next;
	}
	return (size);
}

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

t_token	*fill_operator(t_token *lst, char ***cmd_tab)
{
	size_t	i;

	i = 0;
	*cmd_tab = ft_calloc(2 + (isredir(*lst) && lst->next->type == WORD), sizeof(char *));
	if (!*cmd_tab)
		return (lst);
	(*cmd_tab)[i++] = lst->content;
	if (isredir(*lst) && lst->next->type == WORD)
	{
		lst = lst->next;
		(*cmd_tab)[i++] = lst->content;
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

char	***command_table(t_minishell *sh)
{
	char	***cmd_tab;
	t_token	*curr;
	size_t	tab_size;
	size_t	i;
	
	i = 0;
	curr = sh->lst.head;
	tab_size = malloc_size(curr);
	cmd_tab = ft_calloc(tab_size + 1, sizeof(char **));
	if (!cmd_tab)
		return (NULL);
	while (i < tab_size)
	{
		curr = fill_line(curr, cmd_tab, &i);
		if (!cmd_tab[i])
			return (ft_free_table(cmd_tab), NULL);
		i++;
	}
	sh->cmd_tab = cmd_tab;
	return (cmd_tab);
}

void	command_table_print(char ***cmd_tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd_tab[i])
	{
		j = 0;
		printf("{ ");
		while (cmd_tab[i][j])
		{
			if (j == 0)
				printf("%s", cmd_tab[i][j]);
			else
				printf(" %s", cmd_tab[i][j]);
			j++;
		}
		printf(" }\n");
		i++;
	}
}
