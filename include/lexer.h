/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 10:19:04 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils.c
char	*ft_strset(char *s, char *set);
int		is_valid_variable_char(int c);
int		find_end_of_variable_name(char *s);

// heredoc_find_delimeters.c
void	heredoc_find_delimeters(t_tlist *lst);

// input_parsing.c
t_token	*token_create_from_input(t_token *prev_token, char *input,
			enum e_quotes is_quoted);
