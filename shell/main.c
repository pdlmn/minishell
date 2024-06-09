/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:45:20 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/09 16:52:34 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_or_get_exit_status(enum e_access_flag flag, int new_status)
{
	static int	last_exit_status;

	if (flag == SET)
		last_exit_status = new_status;
	return (last_exit_status);
}

int	handle_prompt_syntax_errors(t_minishell *sh, char *input)
{
	t_err_src			e;

	e = check_errors(&sh->lst);
	if (e.code != NO_ERRORS)
	{
		print_error_message(&e);
		token_list_free(&sh->lst);
		free(input);
		sh->last_status = set_or_get_exit_status(SET, 2);
		return (0);
	}
	return (1);
}

int	sh_cleanup(t_minishell *sh, char *input)
{
	ht_free_table(&sh->env);
	ft_free_table(sh);
	token_list_free(&sh->lst);
	free(input);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	static t_minishell	sh;

	if (!(argc == 1 || argc == 3))
	{
		ft_putstr_fd("mishell: incorrect usage\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!env_init(env, &sh))
		return (EXIT_FAILURE);
	if (argc == 1)
		return (launch_interacrive_mode(&sh));
	else if (argc == 3)
		return (launch_noninteractive_mode(&sh, argv));
}
