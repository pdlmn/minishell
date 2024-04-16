/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:17:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/16 17:58:34 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// expand_quotes.c
t_tlist	*expand_quotes(t_tlist *lst);
t_tlist	*remove_quotes(t_tlist *lst);

// expand_variables.c
t_tlist	*expand_variables(t_tlist *lst, t_ht_table *ht);

// utils.c
t_tlist	*join_unspaced_words(t_tlist *lst);
t_token	*merge_word_tokens(t_token *t1, t_token *t2);
t_token	*token_delete_and_free(t_tlist *lst, t_token *t);
t_token	*token_delete(t_tlist *lst, t_token *t);
t_token	*token_convert_to_empty_word(t_token *t);
t_token	*token_convert_to_word(t_token *t);
