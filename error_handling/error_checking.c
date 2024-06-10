/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:46:40 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 10:40:43 by emuminov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_err_src	wrap_err_src(t_token *t, enum e_err_code err)
{
	t_err_src	res;

	res.t = t;
	res.code = err;
	return (res);
}

void	print_error_message(t_err_src *err)
{
	if (err->code == NO_OPERAND)
		ft_putstr_fd("mishell: " RED "syntax error" RESET_COLOR
			" near unexpected token: 'newline'\n", STDERR_FILENO);
	else if (err->code == BAD_OPERAND)
	{
		ft_putstr_fd("mishell: " RED "syntax error" RESET_COLOR
			" near unexpected token: '", STDERR_FILENO);
		ft_putstr_fd(err->t->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else if (err->code == UNCLOSED_QUOTE)
	{
		ft_putstr_fd("mishell: " RED "unclosed quote" RESET_COLOR " ",
			STDERR_FILENO);
		ft_putstr_fd(err->t->content, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("mishell: no errors\n", STDERR_FILENO);
}

static t_err_src	check_operands(t_token *operator)
{
	if (!operator->next)
		return (wrap_err_src(NULL, NO_OPERAND));
	else if (operator->op_type == PIPE && !operator->prev)
		return (wrap_err_src(operator, BAD_OPERAND));
	else if ((operator->op_type != PIPE && operator->next->type == OPERATOR)
		|| (operator->op_type == PIPE && operator->next->op_type == PIPE))
		return (wrap_err_src(operator->next, BAD_OPERAND));
	return (wrap_err_src(NULL, NO_ERRORS));
}

static t_err_src	check_if_quote_is_closed(t_token *quote)
{
	t_token	*curr;

	curr = quote->next;
	while (curr)
	{
		if (curr->is_quoted == END_QUOTE)
			return (wrap_err_src(NULL, NO_ERRORS));
		curr = curr->next;
	}
	return (wrap_err_src(quote, UNCLOSED_QUOTE));
}

t_err_src	check_errors(t_tlist *lst)
{
	t_err_src	c;
	t_token		*curr;

	curr = lst->head;
	c = wrap_err_src(NULL, NO_ERRORS);
	while (curr)
	{
		if (curr->type == OPERATOR)
			c = check_operands(curr);
		else if (curr->is_quoted == START_QUOTE)
			c = check_if_quote_is_closed(curr);
		if (c.code != NO_ERRORS)
			return (c);
		curr = curr->next;
	}
	return (c);
}
