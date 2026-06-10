/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:30:47 by juljin            #+#    #+#             */
/*   Updated: 2026/04/15 17:30:47 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to check for incomplete input at the end of the line */
int	is_incomplete_token(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (0);
	last = token_get_last(tokens);
	return (last && is_link(last));
}

/* Verifies unclosed parenthesis for bonus only */
int	is_unclosed_paren(t_token *tokens)
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
		curr = curr->next;
	}
	return (balance > 0);
}

/* Helper function to check if a token is a command separator or parenthesis */
int	is_logical_connector(t_token *token)
{
	if (token->type == TK_PIPE || token->type == TK_OR || token->type == TK_AND
		|| token->type == TK_LPAREN || token->type == TK_RPAREN)
		return (1);
	return (0);
}
