/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:21:28 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/14 17:00:14 by juljin           ###   ########.fr       */
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

/* Helper to handle syntax errors for redirections (<, >, <<, >>) */
static int	check_operator_syntax(t_shell *s, t_token *token)
{
	if (!is_operator(token))
		return (1);
	if (!token->next)
	{
		s->last_exit_code = 2;
		print_error_op(ERROR_OPERATOR, "newline");
		return (0);
	}
	if (is_operator(token->next) || is_link(token->next))
	{
		s->last_exit_code = 2;
		print_error_op(ERROR_OPERATOR, token->next->value);
		return (0);
	}
	return (1);
}

/* Helper to handle syntax errors for links (|, ||, &&) */
static int	check_link_syntax(t_shell *s, t_token *token)
{
	if (!is_link(token))
		return (1);
	if (token->next && (is_link(token->next) || is_operator(token->next)))
	{
		s->last_exit_code = 2;
		print_error_op(ERROR_OPERATOR, token->next->value);
		return (0);
	}
	if (!token->next && token->type != TK_PIPE)
	{
		s->last_exit_code = 2;
		print_error("minishell: syntax error", "", "unexpected end of file");
		return (0);
	}
	return (1);
}

/* 
 * Handle syntax error for builtins with redirection or injection operators
 * e.g "cd >>>", "cd hello >", "cd >>"
 */
int	handle_op_error(t_shell *s, t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (!handle_link(tokens))
	{
		s->last_exit_code = 2;
		return (0);
	}
	while (curr)
	{
		if (!handle_special_cases(curr))
		{
			s->last_exit_code = 2;
			return (0);
		}
		if (!check_operator_syntax(s, curr))
			return (0);
		if (!check_link_syntax(s, curr))
			return (0);
		curr = curr->next;
	}
	return (1);
}
