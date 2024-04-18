/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:41:59 by omougel           #+#    #+#             */
/*   Updated: 2024/06/04 16:56:35 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/command_table.h"

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
