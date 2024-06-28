/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:45:06 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/28 16:47:03 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cd_arguments(char **cmd)
{
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] != '\0')
		return (ft_putstr_fd("mishell: cd: invalid option\n", 2), 1);
	if (cmd[1] && cmd[2])
		return (set_or_get_exit_status(SET, 1),
			ft_putstr_fd("mishell: cd: too many arguments\n", 2), 1);
	return (0);
}
