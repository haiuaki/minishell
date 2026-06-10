/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:30:15 by juljin            #+#    #+#             */
/*   Updated: 2026/03/26 18:10:05 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Duplicates a `t_env` node with all its properties */
static t_env	*dup_env_node(t_env *node)
{
	t_env	*new_node;

	if (!node)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(node->key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (node->value)
		new_node->value = ft_strdup(node->value);
	else
		new_node->value = NULL;
	new_node->is_exported = node->is_exported;
	new_node->empty_start = node->empty_start;
	new_node->next = NULL;
	return (new_node);
}

/*
 * Helper function to add a `new_node` in a linked list in its correct
 * sorted position based on its value.
 * Examines through the sorted linked list and compare the values of the node
 * with the one from the `new_node`.
 * (> 0 : value of the `new_node` comes before the node) 
 * This will sort the list in an ascending order based on their ascii value.
 */
static void	sorted_insert(t_env **head_ptr, t_env *new_node)
{
	t_env	*current;

	if (*head_ptr == NULL || ft_strcmp((*head_ptr)->key, new_node->key) > 0)
	{
		new_node->next = *head_ptr;
		*head_ptr = new_node;
	}
	else
	{
		current = *head_ptr;
		while (current->next
			&& ft_strcmp(current->next->key, new_node->key) < 0)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}

/*
 * Duplicates the nodes from the original `t_env` linked list and
 * adds the nodes to a new sorted linked list.
 */
t_env	*get_sorted_env(t_env *original_list)
{
	t_env	*sorted_list;
	t_env	*current;
	t_env	*new_node;

	sorted_list = NULL;
	current = original_list;
	while (current)
	{
		if (current->is_exported)
		{
			new_node = dup_env_node(current);
			if (!new_node)
			{
				free_env_list(sorted_list);
				return (NULL);
			}
			sorted_insert(&sorted_list, new_node);
		}
		current = current->next;
	}
	return (sorted_list);
}
