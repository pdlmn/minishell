/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:41:59 by omougel           #+#    #+#             */
/*   Updated: 2024/05/10 16:27:15 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	isredir(t_token node)
{
	return (node.op_type != PIPE && node.op_type != NOT_OPERATOR);
}

static int	is_word(enum e_token type)
{
	return (type == WORD || type == DELIM || type == QDELIM);
}

void	ft_free_table(char ***tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
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
	*cmd_tab = ft_calloc(2 + (isredir(*lst) && is_word(lst->next->type)) + (lst->op_type == HEREDOC && lst->next->type == QDELIM), sizeof(char *));
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

char	***command_table(t_minishell *sh)
{
	t_token	*curr;
	size_t	tab_size;
	size_t	i;
	
	i = 0;
	curr = sh->lst.head;
	tab_size = malloc_size(curr);
	sh->cmd_tab = ft_calloc(tab_size + 1, sizeof(char **));
	if (!sh->cmd_tab)
		return (NULL);
	while (i < tab_size)
	{
		curr = fill_line(curr, sh->cmd_tab, &i);
		if (!sh->cmd_tab[i])
			return (ft_free_table(sh->cmd_tab), NULL);
		i++;
	}
	sh->cmd_tab[i] = NULL;
	return (sh->cmd_tab);
}

void	command_table_print(char ***cmd_tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd_tab && cmd_tab[i])
	{
		j = 0;
		printf("{ ");
		while (cmd_tab[i][j])
		{
			if (j == 0)
				printf("%s", cmd_tab[i][j]);
			else
				printf(" %s", cmd_tab[i][j]);
			if (cmd_tab[i][j + 1])
				printf(", ");
			j++;
		}
		printf(" }\n");
		i++;
	}
}
/*
int	main(int argc, char **argv)
{
	static t_minishell	sh;
	char	***cmd_tab;
	size_t	i;

	i = 0;
	if (argc != 2)
	{
		printf("Enter proper command\n");
		return (EXIT_FAILURE);
	}
	lexer(argv[1], &sh);
	token_list_print(&sh.lst);
	cmd_tab = command_table(sh.lst.head);
	if (!cmd_tab)
		return (EXIT_FAILURE);
	while (cmd_tab && cmd_tab[i])
		print_arr(cmd_tab[i++]);
	ft_free_table(cmd_tab);
	token_list_free(&sh.lst);
}*/
