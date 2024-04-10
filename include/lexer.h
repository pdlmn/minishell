/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/10 18:22:03 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SPECIAL_SYMBOLS "\"'~$><|"
#define OPERATOR_SYMBOLS "><|"
#define NON_OPERATOR_SYMBOLS "\"'~$"
#define EXPANSION_SYMBOLS "~$"
#define QUOTES_SYMBOLS "'\""
#define QUOTE_CHAR '\''
#define DQUOTE_CHAR '"'
#define SIGIL_CHAR '$'

typedef struct s_tlist
{
	t_token		*head;
	t_token		*tail;
}				t_tlist;

// utils.c
enum e_operator	get_operator(char *str);
enum e_token	get_type(char *str);
char			*ft_strset(char *s, char *set);

// token_operations.c
void			token_list_append(t_tlist *lst, t_token *token);
void			token_list_free(t_token *lst);
void			token_free(t_token *lst);
void			token_list_print(t_token *lst);

// token_creation.c
t_token			*token_create_from_input(char *input, enum e_quotes is_quoted);
