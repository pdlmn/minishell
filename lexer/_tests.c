/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:29:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/21 13:33:26 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

int	main(void)
{
	t_token	*lst;

	lst = lexer("echo <\"hello\"  >>>| \"\"\"''\"'hello'\"''\"\"\" | | asdasda \
zxc <<qw|a \"QUOTED AGAIN A\" 'small quote'");
	token_list_print(lst);
	token_list_free(lst);
}
