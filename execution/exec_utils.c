/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:48:24 by omougel           #+#    #+#             */
/*   Updated: 2024/06/18 15:59:45 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	go_to_next_pipe(char ***cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[i] && ft_strcmp(cmd_tab[i][0], "|"))
		i++;
	return (i);
}

char	*ft_strjoin_cmd(char const *s1, char const *s2)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s1 || !s2 || ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
		return (NULL);
	dest = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = '/';
	while (s2 && s2[i - 1 - ft_strlen(s1)])
	{
		dest[i] = s2[i - 1 - ft_strlen(s1)];
		i++;
	}
	return (dest);
}

void	execute_correct_exit(t_minishell *msh)
{
	ft_putstr_fd("exit\n", 1);
	errno = set_or_get_exit_status(GET, -1);
	ft_exit(msh);
}

void	ft_exit(t_minishell *msh)
{
	token_list_free(&msh->lst);
	ft_free_table_in_child(msh);
	ht_free_table(&msh->env);
	rl_clear_history();
	exit(errno);
}
