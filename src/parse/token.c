/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:43:10 by juljin            #+#    #+#             */
/*   Updated: 2026/02/02 17:50:22 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to add a token type to each token */
void	add_token_type(t_token *token)
{
	if (ft_strcmp(token->value, "|") == 0)
		token->type = TK_PIPE;
	else if (ft_strcmp(token->value, ">") == 0)
		token->type = TK_REDIR_OUT;
	else if (ft_strcmp(token->value, "<") == 0)
		token->type = TK_REDIR_OUT;
	else if (ft_strcmp(token->value, ">>") == 0)
		token->type = TK_APPEND;
	else if (ft_strcmp(token->value, "<<") == 0)
		token->type = TK_HEREDOC;
	else
		token->type = TK_WORD;
}

/* Breaks the input into tokens and categorizes them with `add_token_type` */
t_token	lexer()
{
	
}

void	free_token_node(t_token *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	free(node);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		free_token_node(head);
		head = tmp;
	}
}
