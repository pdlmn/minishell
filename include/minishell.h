/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:34:14 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/20 14:46:51 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

enum	e_token_type
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
enum	e_operator_type
{
	NOT_OPERATOR,
	IN_REDIR,        
	OUT_REDIR,       
	HEREDOC,         
	OUT_REDIR_APPEND,
	PIPE,            
};

typedef struct	s_token
{
	struct s_token			*next;
	char					*content;
	enum e_token_type		type;
	enum e_operator_type	op_type;
}				t_token;

