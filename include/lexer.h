/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:38:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/09 15:05:55 by emuminov         ###   ########.fr       */
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


enum e_operator	get_operator(char *str);
enum e_token	get_type(char *str);
char			*dup_quoted(char quote, int *i, char *input);
char			*dup_until_next_space(int *i, char *input);
char			*dup_operator(int *i, char *input);
t_token			*token_create(char *content, int len, int space_after, enum e_quotes is_quoted);
void			token_list_append(t_tlist *lst, t_token *token);
void			token_list_free(t_token *lst);
void			token_free(t_token *lst);
void			token_list_print(t_token *lst);
char			*ft_strset(char *s, char *set);
