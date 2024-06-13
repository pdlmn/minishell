/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:51:27 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/13 18:03:10 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*read_command(char *prompt)
{
	char	*command;

	command = readline(prompt);
	if (!command)
		return (NULL);
	add_history(command);
	return (command);
}

int	check_if_the_first_arg_is_a_pathname(t_tlist *lst)
{
	int	i;

	i = 0;
	while (lst->head->content[i])
	{
		if (lst->head->content[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	handle_pathname_as_a_first_arg(t_minishell *sh, char *input)
{
	struct stat	path_stat;

	stat(sh->lst.head->content, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("mishell: is a directory\n", STDERR_FILENO);
		set_or_get_exit_status(SET, 126);
		sh_cleanup(sh, input, NULL);
		return (1);
	}
	if (!(path_stat.st_mode & X_OK))
	{
		ft_putstr_fd("mishell: permission denied\n", STDERR_FILENO);
		set_or_get_exit_status(SET, 126);
		sh_cleanup(sh, input, NULL);
		return (1);
	}
	return (0);
}

int	launch_interacrive_mode(t_minishell *sh)
{
	char	*input;

	while (42)
	{
		init_interacrive_signal_handlers();
		input = read_command(PROMPT);
		if (input == NULL)
			return (ft_putstr_fd("exit\n", STDOUT_FILENO), sh_cleanup(sh, NULL,
					sh->env), set_or_get_exit_status(GET, -1));
		if (!lex_input(input, &sh->lst))
			return (sh_cleanup(sh, input, sh->env));
		if (!handle_prompt_syntax_errors(sh, input))
			continue ;
		sh->last_status = set_or_get_exit_status(GET, -1);
		if (!expand_tokens(sh, &sh->lst))
			return (sh_cleanup(sh, input, sh->env));
		if (check_if_the_first_arg_is_a_pathname(&sh->lst)
			&& handle_pathname_as_a_first_arg(sh, input))
			continue ;
		if (!command_table(sh))
			return (sh_cleanup(sh, input, sh->env));
		if (sh->cmd_tab[0] && sh->cmd_tab[0][0])
			execute(*sh);
		sh_cleanup(sh, input, NULL);
	}
}
