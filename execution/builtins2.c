/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:52:52 by omougel           #+#    #+#             */
/*   Updated: 2024/06/04 19:16:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	echo_params(char **cmd, int *nl)
{
	int	j;
	int	i;

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
			break ;
		i++;
	}
	return (i);
}

int	echo(char **cmd, int fd_out)
{
	int	nl;
	int	i;

	i = echo_params(cmd, &nl);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd_out);
		if (cmd[i + 1] != NULL)
			ft_putchar_fd(' ', fd_out);
		i++;
	}
	if (nl == 0)
		printf("\n");
	return (0);
}

int	pwd(char **cmd, t_minishell *sh, int fd_out)
{
	char	*pwd;

	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: pwd: invalid option\n", 2), 2);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit(sh);
	ft_putstr_fd(pwd, fd_out);
	ft_putchar_fd('\n', fd_out);
	free(pwd);
	return (0);
}

int	bt_env(char **cmd, t_ht_table *env, int fd_out)
{
	char	**envp;
	int		i;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_putstr_fd("mishell: env: invalid option\n", 2), 2);
	envp = env_ht_to_arr(env);
	while (envp[i])
	{
		ft_putstr_fd(envp[i++], fd_out);
		ft_putchar_fd('\n', fd_out);
	}
	ft_free_split(envp);
	return (0);
}

void	bt_exit(t_minishell *msh)
{
	ft_putstr_fd("exit\n", 2);
	ft_exit(msh);
}
