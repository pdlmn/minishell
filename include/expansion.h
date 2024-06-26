/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:17:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 16:46:19 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "../include/minishell.h"

// expand_quotes.c
t_tlist	*expand_quotes(t_tlist *lst);
t_tlist	*remove_quotes(t_tlist *lst);

// expand_variables.c
t_tlist	*expand_variables(t_minishell *sh, t_tlist *lst);

// split_unspaced.c
t_tlist	*split_spaced_unqouted_tokens(t_tlist *lst);

// utils.c
t_tlist	*join_unspaced_words(t_tlist *lst, int is_in_heredoc);
t_token	*merge_word_tokens(t_token *t1, t_token *t2);
t_token	*token_convert_to_empty_word(t_token *t);
t_token	*token_convert_to_word(t_token *t);
#endif
