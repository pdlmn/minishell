/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:17:12 by emuminov          #+#    #+#             */
/*   Updated: 2024/04/08 18:27:20 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct	s_strnode
{
	char				*str;
	size_t				len;
	struct s_strnode	*next;
}				t_strnode;

typedef struct	s_strlist
{
	t_strnode	*head;
	t_strnode	*tail;
}				t_strlist;

char	*unquote(char *word, int quote);
int		srtrlen_excluding_symbol(char *str, int c);
char	*expand_word(t_ht_table *ht, char *word);
char	*join_expanded_variables(char **vars, char *word);
char	*expand_digit_variable(char *var);




char	*expand_dquoted(t_ht_table *ht, const char *s);

