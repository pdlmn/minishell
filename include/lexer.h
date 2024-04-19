/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/19 15:26:15 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils.c
char			*ft_strset(char *s, char *set);
int				is_valid_variable_char(int c);
int		 		find_end_of_variable_name(char *s);

// heredoc_find_delimeters.c
t_tlist	*heredoc_find_delimeters(t_minishell *sh);

// input_parsing.c
t_token			*token_create_from_input(t_token *prev_token, char *input, enum e_quotes is_quoted);
