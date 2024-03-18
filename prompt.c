/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:04:19 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/18 18:26:47 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

char	*prompt(char *prompt)
{
	char	*command;

	command = readline(prompt);
	if (!command)
		return (NULL);
	add_history(command);
	return (command);
}

/////////////
// TESTING //
/////////////
int	main()
{
	char	*command;

	command = prompt("-> ");
	while (command != NULL)
	{
		command = prompt("-> ");
		free(command);
	}
	rl_clear_history();
}
