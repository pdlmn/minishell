/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/22 15:02:08 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

typedef struct s_tlist
{
	t_token		*head;
	t_token		*tail;
}				t_tlist;

enum e_operator	get_operator(char *str);
enum e_token	get_type(char *str);
char			*dup_quoted(char quote, int *i, char *input);
char			*dup_until_next_space(int *i, char *input);
char			*dup_operator(int *i, char *input);
t_token			*token_create(enum e_token type, enum e_operator op,
					char *content, int space_after);
void			token_list_append(t_tlist *lst, t_token *token);
void			token_list_free(t_token *lst);
void			token_free(t_token *lst);
void			token_list_print(t_token *lst);
