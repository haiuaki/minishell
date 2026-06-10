/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:45:07 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 14:24:48 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Verifies if a character is a quote */
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/* Verifies if a charcter is a separator */
int	is_sep(char c)
{
	return (c == '|' || c == '&' || c == '>' || c == '<' || c == ';'
		|| c == '(' || c == ')');
}

/* Helper function to check whether a token is "<", ">", "<<", ">>" or not */
int	is_operator(t_token *token)
{
	if (token->type == TK_APPEND || token->type == TK_HEREDOC
		|| token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT
		|| token->type == TK_HERESTRING)
		return (1);
	return (0);
}

/* Helper function to check whether a token is "|", "||" or "&&" */
int	is_link(t_token *token)
{
	if (token->type == TK_PIPE || token->type == TK_OR
		|| token->type == TK_AND)
		return (1);
	return (0);
}

/* Sets the token type of each token given their value */
void	set_token_type(t_token *token)
{
	if (ft_strcmp(token->value, "|") == 0)
		token->type = TK_PIPE;
	else if (ft_strcmp(token->value, "||") == 0)
		token->type = TK_OR;
	else if (ft_strcmp(token->value, "&&") == 0)
		token->type = TK_AND;
	else if (ft_strcmp(token->value, ">") == 0)
		token->type = TK_REDIR_OUT;
	else if (ft_strcmp(token->value, "<") == 0)
		token->type = TK_REDIR_IN;
	else if (ft_strcmp(token->value, ">>") == 0)
		token->type = TK_APPEND;
	else if (ft_strcmp(token->value, "<<") == 0)
		token->type = TK_HEREDOC;
	else if (ft_strcmp(token->value, "<<<") == 0)
		token->type = TK_HERESTRING;
	else
		token->type = TK_WORD;
}
