/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:21:28 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/14 15:54:46 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to handle tokens that are not in the token struct */
static int	handle_special_cases(t_token *token)
{
	if (token->next && (token->type == TK_REDIR_OUT
			&& token->next->type == TK_PIPE) && !token->next->next)
		return (print_error_op(ERROR_OPERATOR, "newline"), 0);
	else if (token->next && (token->type == TK_REDIR_IN
			&& token->next->type == TK_REDIR_OUT && !token->next->next))
		return (print_error_op(ERROR_OPERATOR, "newline"), 0);
	else if (token->next && token->type == TK_REDIR_OUT
		&& token->next->type == TK_REDIR_IN)
		return (print_error_op(ERROR_OPERATOR, "newline"), 0);
	else if (token->next && (token->type == TK_REDIR_IN
			|| token->type == TK_APPEND || token->type == TK_HEREDOC
			|| token->type == TK_HERESTRING) && token->next->type == TK_PIPE)
		return (print_error_op(ERROR_OPERATOR, "|"), 0);
	else if (token->next && token->next->next && token->type == TK_APPEND
		&& token->next->type == TK_REDIR_OUT
		&& token->next->next->type == TK_PIPE)
		return (print_error_op(ERROR_OPERATOR, ">|"), 0);
	else
		return (1);
}

/* Helper to check all token syntax errors in the token list */
static int	check_tokens_loop(t_shell *s, t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (!handle_special_cases(curr) || !check_operator_syntax(s, curr)
			|| !check_link_syntax(s, curr) || !check_paren_syntax(s, curr))
			return (0);
		curr = curr->next;
	}
	return (1);
}

/* Handle syntax error for builtins with redirection or injection operators */
int	handle_op_error(t_shell *s, t_token *tokens)
{
	if (!handle_link(tokens))
	{
		s->last_exit_code = 2;
		return (0);
	}
	if (!check_paren_balance(s, tokens))
		return (0);
	return (check_tokens_loop(s, tokens));
}
