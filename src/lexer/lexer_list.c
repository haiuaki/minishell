/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:30:32 by juljin            #+#    #+#             */
/*   Updated: 2026/04/02 12:31:16 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Appends a node to the end of the list */
void	token_add_back(t_token **head, t_token *new_node)
{
	t_token	*current;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

/* Gets the last node of the token list */
t_token	*token_get_last(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

/* Counts the number of node in the token list */
size_t	token_list_size(t_token *head)
{
	t_token	*current;
	size_t	count;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/* 
 * Helper function to determine if the token list ends with a pipe (|)
 * in mandatory mode.
 */
int	is_incomplete_mandatory(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (0);
	last = token_get_last(tokens);
	if (last && last->type == TK_PIPE)
		return (1);
	return (0);
}
