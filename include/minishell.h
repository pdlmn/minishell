/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:34:14 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/21 14:32:58 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

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

t_token				*lexer(char *input);
void				token_list_free(t_token *lst);
void				token_list_print(t_token *lst);
