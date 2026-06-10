/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 13:18:28 by juljin            #+#    #+#             */
/*   Updated: 2026/03/06 12:10:12 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If the first character of a node's value is a `~` and unquoted,
 * checks if it's a single char or if the following char is `~`.
 * If yes, expands the tilde to the `$HOME` value.
 * Else, doesn't do anything.
 */
void	expand_tilde(t_env *env, t_expand *exp, size_t *i)
{
	char	*home;

	home = NULL;
	if (exp->val[0] == '~' && exp->meta[0] == 'N'
		&& (!exp->val[1] || exp->val[1] == '/'))
	{
		home = env_get_value(env, "HOME");
		if (!home)
			return ;
		exp->new_val = join_and_free(exp->new_val, home);
		if (!exp->new_val)
			return (free(home));
		*i = 1;
	}
}
