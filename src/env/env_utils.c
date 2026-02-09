/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:00:23 by juljin            #+#    #+#             */
/*   Updated: 2026/02/09 12:26:50 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Splitting the key and its value & storing it inside a node, ignoring '=' */
t_env	*env_new_node(char *str)
{
	t_env	*node;
	char	*equal_ptr;
	size_t	key_len;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	equal_ptr = ft_strchr(str, '=');
	if (equal_ptr)
	{
		key_len = equal_ptr - str;
		if (key_len == 0)
			return (free_env_node(node), NULL);
		node->key = ft_substr(str, 0, key_len);
		node->value = ft_strdup(equal_ptr + 1);
	}
	else
		node->key = ft_strdup(str);
	if (!node->key || (equal_ptr && !node->value))
		return (free_env_node(node), NULL);
	return (node);
}

/* Adding the node at the end of the list */
void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*current;

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

/* Search and retrieve the associated value of the given key in the env */
char	*env_get_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (key);
}
