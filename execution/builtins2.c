/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:52:52 by omougel           #+#    #+#             */
/*   Updated: 2024/06/02 00:53:50 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	echo_params(char **cmd, int *nl)
{
	int	j;
	int i;

	*nl = 0;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		if (cmd[i][j] == '\0')
			return (i);
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
			*nl = 1;
		else
			break;
		i++;
	}
	return (i);
}

int	echo(char **cmd, t_ht_table *env)
{
	int	nl;
	int i;

	(void)env;
	i = echo_params(cmd, &nl);
	while (cmd[i])
	{
		printf("%s%c", cmd[i], ' ' * (cmd[i + 1] != NULL));
		i++;
	}
	if (nl == 0)
		printf("\n");
	return (0);
}

int	pwd(char **cmd, t_ht_table *env)
{
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: pwd: invalid option\n", 2), 2);
	printf("%s\n", ht_get(env, "PWD"));//if PWD has been changed need to display the right thing anyway
	return (0);
}

int	bt_env(char **cmd, t_ht_table *env)
{
	char  **envp;
	int	  i;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: env: invalid option\n", 2), 2);
	envp = env_ht_to_arr(env);
	while (envp[i])
		printf("%s\n", envp[i++]);
	free(envp);
	return (0);
}

void  bt_exit(t_minishell *msh)
{
	ft_putstr_fd("exit", 2);
	ft_exit(msh);
}
