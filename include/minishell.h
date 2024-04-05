/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:34:14 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/05 18:17:09 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

enum				e_token
{
	WORD,
	OPERATOR,
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

typedef struct s_token
{
	struct s_token	*next;
	char			*content;
	enum e_token	type;
	enum e_operator	op_type;
	int				space_after;
}					t_token;

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

t_token				*lexer(char *input);
void				token_list_free(t_token *token);
void				token_list_print(t_token *token);

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
