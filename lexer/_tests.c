/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tests.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:29:46 by emuminov          #+#    #+#             */
/*   Updated: 2024/03/21 15:27:52 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

int	main(void)
{
	t_token	*lst;

	// echo 1 < 0 hello 1 >> 0 > 0 | 1 "''" 0 'hello' 0 "''" 1 | 1 | 1 asdasda 1 zxc 1 << 0 qw 0 | 0 a 1 "QU..A" 1 'small quote' 0
	lst = lexer("\"\"echo\"\" <\"hello\"  >>>| \"\"\"''\"'hello'\"''\"\"\" | | asdasda \
zxc <<qw|a \"QUOTED AGAIN A\" 'small quote'''");
	token_list_print(lst);
	token_list_free(lst);
}
