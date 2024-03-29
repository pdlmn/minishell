/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/29 17:40:00 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_table.h"
#include <stdio.h>

int	main(void)
{
	t_ht_table	*ht;

	ht = ht_new();
	ht_set(ht, "USER", "emuminov");
	ht_set(ht, "LANG", "en_US.UTF-8");
	ht_set(ht, "LESS", "-R");
	ht_set(ht, "XDG_SESSION_TYPE", "x11");
	ht_set(ht, "VTE_VERSION", "6003");
	ht_set(ht, "ZELLIJ", "0");
	ht_set(ht, "SHLVL", "2");
	ht_set(ht, "PAGER", "less");
	ht_set(ht, "OLDPWD", "/home/emuminov/projects/");
	ht_set(ht, "PWD", "/home/emuminov/projects/minishell/");
	ht_set(ht, "HOME", "/home/emuminov/");
	ht_set(ht, "DISPLAY", ":0");
	ht_set(ht, "COLORTERM", "truecolor");
	ht_table_print(ht);
	ht_table_free(ht);
}
