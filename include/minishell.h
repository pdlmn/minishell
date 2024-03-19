/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:34:14 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/19 14:39:47 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

enum	e_token_type
{
	WORD,
	OPERATOR,
};

enum	e_operator_type
{
	NOT_OPERATOR,
	INPUT_REDIRECTION,
	OUTPUT_REDIRECTION,
	DELIMITER_READ,
	OUTPUT_APPEND,
	PIPE,
};

typedef struct	s_token
{
	struct s_token			*next;
	char					*content;
	enum e_token_type		type;
	enum e_operator_type	op_type;
}				t_token;

