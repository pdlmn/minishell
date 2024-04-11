/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 16:13:31 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils.c
enum e_operator	get_operator(char *str);
enum e_token	get_type(char *str);
char			*ft_strset(char *s, char *set);

// token_operations.c
void			token_list_append(t_tlist *lst, t_token *token);
void			token_free(t_token *lst);

// token_creation.c
t_token			*token_create_from_input(t_token *prev_token, char *input, enum e_quotes is_quoted);
