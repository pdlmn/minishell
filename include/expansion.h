/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:17:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/04 12:49:52 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*unquote(char *word, int quote);
int		srtrlen_excluding_symbol(char *str, int c);
char	*expand_word(t_ht_table *ht, char *word);
char	*join_expanded_variables(char **vars, char *word);
char	*expand_digit_variable(char *var);
