/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:23:17 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 17:55:55 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_table.h"

int	main(void)
{
	t_ht_table	*ht;

	ht = ht_new(100);
	ht_set(ht, "USER", "emuminov");
	ht_set(ht, "LANG", "en_US.UTF-8");
	ht_set(ht, "LESS", "-R");
	ht_set(ht, "LESS", "-R");
	ht_set(ht, "LESS", "-R");
	ht_set(ht, "LESS", "-R");
	ht_set(ht, "XDG_SESSION_TYPE", "x11");
	ht_set(ht, "VTE_VERSION", "6003");
	ht_set(ht, "ZELLIJ", "0");
	ht_set(ht, "SHLVL", "2");
	ht_set(ht, "PAGER", "less");
	ht_delete(ht, "PAGER");
	ht_set(ht, "OLDPWD", "/home/emuminov/projects/");
	ht_set(ht, "OLDPWD", "/home/emuminov/projects/");
	ht_set(ht, "OLDPWD", "/home/emuminov/projects/");
	ht_set(ht, "OLDPWD", "/home/emuminov/projects/");
	ht_delete(ht, "OLDPWD");
	ht_set(ht, "PWD", "/home/emuminov/projects/minishell/");
	ht_delete(ht, "PWD");
	ht_set(ht, "HOME", "/home/emuminov/");
	ht_delete(ht, "HOME");
	ht_delete(ht, "HOME");
	ht_delete(ht, "HOME");
	ht_delete(ht, "HOME");
	ht_set(ht, "DISPLAY", ":0");
	ht_delete(ht, "DISPLAY");
	ht_set(ht, "COLORTERM", "truecolor");
	ht_delete(ht, "COLORTERM");
	ht_print_table(ht);
	ht_print_buckets(ht);
	printf("\nLANG is %s\n\n", ht_get(ht, "LANG"));
	printf("\nZELLIJ is %s\n\n", ht_get(ht, "ZELLIJ"));
	printf("\nCOLORTERM is %s\n\n", ht_get(ht, "COLORTERM"));
	printf("\nUSER is %s\n\n", ht_get(ht, "USER"));
	printf("\nHOME is %s\n\n", ht_get(ht, "HOME"));
	ht_free_table(ht);
}
