/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:09:33 by juljin            #+#    #+#             */
/*   Updated: 2026/03/24 18:05:58 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * If the `keylen` > 0, a key exists and it can be expanded.
 * Retrieves the value of the variable in the environment list,
 * and joins it to the stashed input.
 * If the key is `?` or `0`, expands to the exit code or the shell name
 */
void	expand_variable(t_shell *s, t_expand *exp, size_t *i)
{
	char	*exit_code;

	if (exp->keylen == 1 && exp->val[*i] != '_')
	{
		if (exp->val[*i] == '0')
			exp->new_val = join_and_free(exp->new_val, ft_strdup("minishell"));
		else if (exp->val[*i] == '?')
		{
			exit_code = ft_itoa(s->last_exit_code);
			if (!exit_code)
				exit_code = ft_strdup("1");
			exp->new_val = join_and_free(exp->new_val, exit_code);
		}
		*i += exp->keylen;
		return ;
	}
	exp->sub = ft_substr(exp->val, *i, exp->keylen);
	exp->key_val = env_get_value(s->env_list, exp->sub);
	free(exp->sub);
	if (exp->key_val)
		exp->new_val = join_and_free(exp->new_val, exp->key_val);
	*i += exp->keylen;
}
