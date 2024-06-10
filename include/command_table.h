/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:24:53 by omougel           #+#    #+#             */
/*   Updated: 2024/06/10 10:56:21 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include "minishell.h"

t_token	*fill_line(t_token *lst, char ***cmd_tab, size_t *i);
size_t	cmd_size(t_token *lst);
t_token	*jump_redir(t_token *lst);
t_token	*find_redir(t_token **lst);
size_t	malloc_size(t_token *lst);
int		isredir(t_token node);
int		is_word(enum e_token type);
#endif
