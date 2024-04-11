/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:34:14 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/11 19:45:41 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

enum				e_token
{
	WORD,
	OPERATOR,
	SQUOTE,
	DQUOTE,
	TILDE,
	SIGIL,
};

/*
 * IN_REDIR         = <
 * OUT_REDIR        = >
 * HEREDOC          = <<
 * OUT_REDIR_APPEND = >>
 * PIPE             = |
 * */
enum				e_operator
{
	NOT_OPERATOR,
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
	OUT_REDIR_APPEND,
	PIPE,
};

enum				e_quotes
{
	NOT_QUOTED,
	SQUOTED,
	DQUOTED,
	START_QUOTE,
	END_QUOTE,
};

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
	char			*content;
	int				len;
	enum e_quotes	is_quoted;
	enum e_token	type;
	enum e_operator	op_type;
	int				space_after;
}					t_token;

typedef struct s_tlist
{
	t_token		*head;
	t_token		*tail;
}				t_tlist;

typedef struct s_ht_item
{
	char			*key;
	char			*value;
	int				is_deleted;
}					t_ht_item;

typedef struct s_ht_table
{
	int				base_size;
	int				size;
	int				count;
	t_ht_item		**items;
}					t_ht_table;

t_tlist				*lexer(char *input);
void				token_list_append(t_tlist *lst, t_token *t);
void				token_list_free(t_tlist *token);
void				token_list_print(t_tlist *token);

t_token				*token_create(char *content, int len, int space_after, enum e_quotes is_quoted);
void				token_free(t_token *token);

void				ft_free_table(char ***tab);

t_ht_table			*ht_new(int base_size);
void				ht_free_table(t_ht_table *ht);
t_ht_item			*ht_set(t_ht_table *ht, const char *key, const char *value);
void				ht_delete(t_ht_table *ht, const char *key);
char				*ht_get(t_ht_table *ht, const char *key);
void				ht_print_buckets(t_ht_table *ht);
void				ht_print_table(t_ht_table *ht);

t_ht_table			*env_init(char **env);
char				**env_ht_to_arr(t_ht_table *ht);

t_tlist				*expansion(t_tlist *lst, t_ht_table *ht);
