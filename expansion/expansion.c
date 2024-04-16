/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:16:56 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/16 20:36:06 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

t_tlist	*expansion(t_minishell *sh)
{
	if (!expand_variables(sh))
		return (NULL);
	if (!expand_quotes(&sh->lst))
		return (NULL);
	if (!remove_quotes(&sh->lst))
		return (NULL);
	if (!join_unspaced_words(&sh->lst))
		return (NULL);
	return (&sh->lst);
}
