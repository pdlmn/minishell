/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:52:52 by omougel           #+#    #+#             */
/*   Updated: 2024/06/28 17:45:27 by emuminov         ###   ########.fr       */
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

void	echo(char **cmd, int fd_out)
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
		ft_putstr_fd("\n", fd_out);
	set_or_get_exit_status(SET, 0);
}

void	pwd(char **cmd, t_minishell *sh, int fd_out)
{
	char	*pwd;

	if (cmd[1] && cmd[1][0] == '-')
		return (set_or_get_exit_status(SET, 2),
			ft_putstr_fd("mishell: pwd: invalid option\n", 2));
	pwd = getcwd(NULL, 0);
	if (!pwd && ht_get(sh->env, "PWD"))
	{
		pwd = ft_strdup(ht_get(sh->env, "PWD"));
		if (!pwd)
			ft_exit(sh);
	}
	else if (!pwd && !ht_get(sh->env, "PWD"))
		return (set_or_get_exit_status(SET, 1),
			ft_putstr_fd("mishell: pwd: no such file or directory\n", 2));
	ft_putstr_fd(pwd, fd_out);
	ft_putchar_fd('\n', fd_out);
	free(pwd);
	set_or_get_exit_status(SET, 0);
}

void	bt_env(char **cmd, t_ht_table *env, int fd_out, t_minishell *sh)
{
	char	**envp;
	int		i;

	i = 0;
	if (cmd[1] && cmd[1][0] == '-')
		return (set_or_get_exit_status(SET, 2),
			ft_putstr_fd("mishell: env: invalid option\n", 2));
	envp = env_ht_to_arr(env);
	if (!envp)
		ft_exit(sh);
	while (envp[i])
	{
		ft_putstr_fd(envp[i++], fd_out);
		ft_putchar_fd('\n', fd_out);
	}
	ft_free_split(envp);
	set_or_get_exit_status(SET, 0);
}

void	bt_exit(char **cmd, t_minishell *msh)
{
	int	i;

	i = 0;
	if (!cmd[1])
		execute_correct_exit(msh);
	while (ft_isspace(cmd[1][i]))
		i++;
	if ((cmd[1][i] != '\0' && cmd[1][i] != '-' && cmd[1][i] != '+' &&
		!ft_isdigit(cmd[1][i])))
		err_msg(msh);
	while (cmd[1][++i])
		if (!ft_isdigit(cmd[1][i]))
			err_msg(msh);
	errno = (unsigned char)(ft_atoi(cmd[1])) % 256;
	if (cmd[2] != NULL)
	{
		ft_putstr_fd("mishell: exit: too many arguments\n", 2);
		errno = set_or_get_exit_status(SET, 1);
	}
	if (msh->cmd_nbr != 1)
		set_or_get_exit_status(SET, errno);
	else
		return (ft_putstr_fd("exit\n", 1), ft_exit(msh));
}
