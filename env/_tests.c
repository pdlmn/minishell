/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:05:18 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/05 18:20:27 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"

int	main(int argc, char **argv, char **env)
{
	t_ht_table	*ht;
	char		**env_arr;
	int			i;

	(void)argc;
	(void)argv;
	ht = env_init(env);
	printf("===ht_print_table:===\n");
	ht_print_table(ht);
	env_arr = env_ht_to_arr(ht);
	printf("\n\n===env_arr:===\n");
	i = 0;
	while (env_arr[i])
		printf("%s\n", env_arr[i++]);
	ft_free_split(env_arr);
	ht_free_table(ht);
}
