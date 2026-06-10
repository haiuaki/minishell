/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:40:59 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 16:39:52 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Finds if the token is `;' and `&`*/
static int	is_spe_op(t_token *tokens)
{
	if (ft_strcmp(tokens->value, ";") == 0
		|| ft_strcmp(tokens->value, "&") == 0)
		return (1);
	return (0);
}

/* 
 * Helper function to handle `|`, `||`, `&` and `&&` syntax errors
 * The `tokens` could be NULL in case the tokenization fails
 * because of opened quotes.
 * Returns 1 to skip the syntax checks.
 * 0 otherwise so the input processer can free the list and continue.
 */
int	handle_link(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (is_link(tokens) || is_spe_op(tokens))
	{
		if (tokens->type == TK_PIPE)
			print_error_op(ERROR_OPERATOR, "|");
		else if (tokens->type == TK_OR)
			print_error_op(ERROR_OPERATOR, "||");
		else if (tokens->type == TK_AND)
			print_error_op(ERROR_OPERATOR, "&&");
		else if (ft_strcmp(tokens->value, "&") == 0)
			print_error_op(ERROR_OPERATOR, "&");
		else if (ft_strcmp(tokens->value, ";") == 0)
		{
			if (tokens->next
				&& ft_strcmp(tokens->next->value, ";") == 0)
				print_error_op(ERROR_OPERATOR, ";;");
			else
				print_error_op(ERROR_OPERATOR, ";");
		}
		return (0);
	}
	return (1);
}
