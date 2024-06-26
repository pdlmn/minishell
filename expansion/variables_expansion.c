/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuminov <emuminov@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:53:09 by emuminov          #+#    #+#             */
/*   Updated: 2024/06/10 10:13:04 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static t_token	*replace_variable_with_value(t_token *sigil, t_minishell *sh,
		t_tlist *lst, char *val)
{
	t_token	*res;
	char	*copied_val;

	res = token_delete_and_free(lst, sigil);
	if (val)
		copied_val = ft_strdup(val);
	else
		copied_val = ft_itoa(sh->last_status);
	if (!copied_val)
		return (NULL);
	free(res->content);
	res->content = copied_val;
	res->len = ft_strlen(copied_val);
	if (sh)
		token_convert_to_word(res);
	return (res);
}

static t_token	*delete_sigil_and_the_next_word(t_tlist *lst, t_token *sigil)
{
	t_token	*res;

	res = token_delete_and_free(lst, sigil);
	if (res->next)
		res = token_delete_and_free(lst, res);
	else
		token_convert_to_empty_word(res);
	return (res);
}

static t_token	*expand_after_sigil(t_minishell *sh, t_tlist *lst,
		t_token *sigil)
{
	char	*val;

	if (!sigil->space_after && sigil->next
		&& sigil->next->op_type == NOT_OPERATOR)
	{
		if (sigil->next->type == DIGIT)
			return (delete_sigil_and_the_next_word(lst, sigil));
		if (sigil->next->type == QMARK)
			return (replace_variable_with_value(sigil, sh, lst, NULL));
		else if (sigil->next->type == WORD)
		{
			val = ht_get(sh->env, sigil->next->content);
			if (!val)
				return (delete_sigil_and_the_next_word(lst, sigil));
			return (replace_variable_with_value(sigil, sh, lst, val));
		}
		else if ((sigil->next->type == SQUOTE || sigil->next->type == DQUOTE)
			&& sigil->is_quoted == NOT_QUOTED)
			return (token_delete_and_free(lst, sigil));
		else if ((sigil->next->type == DQUOTE && sigil->is_quoted == DQUOTED)
			|| sigil->next->type == OTHER)
			return (token_convert_to_word(sigil));
	}
	return (token_convert_to_word(sigil));
}

static t_token	*expand_tilde(t_ht_table *ht, t_token *tilde)
{
	char	*home_path;
	char	*cloned_home_path;

	if (!tilde->space_after && tilde->next && tilde->next->content[0] != '/')
		return (token_convert_to_word(tilde));
	home_path = ht_get(ht, "HOME");
	if (!home_path)
		return (token_convert_to_empty_word(tilde));
	cloned_home_path = ft_strdup(home_path);
	if (!cloned_home_path)
		return (NULL);
	free(tilde->content);
	tilde->type = WORD;
	tilde->content = cloned_home_path;
	tilde->len = ft_strlen(cloned_home_path);
	return (tilde);
}

t_tlist	*expand_variables(t_minishell *sh, t_tlist *lst)
{
	t_token	*curr;

	curr = lst->head;
	while (curr)
	{
		if (curr->type == SIGIL)
			curr = expand_after_sigil(sh, lst, curr);
		else if (curr->type == TILDE)
			curr = expand_tilde(sh->env, curr);
		if (!curr)
			return (NULL);
		else
			curr = curr->next;
	}
	return (lst);
}
