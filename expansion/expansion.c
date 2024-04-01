/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/01 05:41:14 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_table.h"

// expand(ht, cmd_tab[j])
//   var = ft_strchr('$', cmd_tab[j])
//   expanded = ht_get(ht, var);
//   len = ft_strlen(expanded) + (var - cmd_tab[j]))

// Variable names can contain uppercase, lowercase letters, numbers, underscores, and digits.
// They can't start with digits.
char	***expansion(t_ht_table *ht, char ***cmd_tab)
{
	// while i
	//   while j
	//     while c
	//       if c == '$' && check_if_valid_variable(&c)
	//         expand(ht, cmd_tab[j])

}
