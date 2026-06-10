/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_error_check_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:00:00 by juljin            #+#    #+#             */
/*   Updated: 2026/04/15 00:00:00 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper to handle syntax errors for redirections (<, >, <<, >>) */
int	check_operator_syntax(t_shell *s, t_token *token)
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
int	check_link_syntax(t_shell *s, t_token *token)
{
	if (!is_link(token))
		return (1);
	if (!token->next)
		return (1);
	if (token->next && (is_link(token->next) || is_operator(token->next)))
	{
		s->last_exit_code = 2;
		print_error_op(ERROR_OPERATOR, token->next->value);
		return (0);
	}
	return (1);
}

/* Helper to handle syntax errors for parentheses */
int	check_paren_syntax(t_shell *s, t_token *token)
{
	if (token->type == TK_LPAREN)
	{
		if (token->next && (is_link(token->next)
				&& token->next->type != TK_PIPE))
		{
			s->last_exit_code = 2;
			print_error_op(ERROR_OPERATOR, token->next->value);
			return (0);
		}
	}
	else if (token->type == TK_RPAREN)
	{
		if (token->next && token->next->type == TK_WORD)
		{
			s->last_exit_code = 2;
			print_error_op(ERROR_OPERATOR, token->next->value);
			return (0);
		}
	}
	return (1);
}

/* Verifies parenthesis balance */
int	check_paren_balance(t_shell *s, t_token *tokens)
{
	t_token	*curr;
	int		balance;

	curr = tokens;
	balance = 0;
	while (curr)
	{
		if (curr->type == TK_LPAREN)
			balance++;
		else if (curr->type == TK_RPAREN)
			balance--;
		if (balance < 0)
		{
			s->last_exit_code = 2;
			print_error_op(ERROR_OPERATOR, ")");
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}
