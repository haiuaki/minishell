/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:45:07 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 09:50:21 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to verify if a character is a quote */
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/* Helper function to verify if a charcter is a separator */
int	is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/* Helper function to add a node to the end of the list */
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

/* Helper function to free a `t_token` node */
void	free_token_node(t_token *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	free(node);
}

/* Helper function to free a `t_token` list */
void	free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free_token_node(head);
		head = tmp;
	}
}
