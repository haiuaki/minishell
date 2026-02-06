/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 00:05:30 by juljin            #+#    #+#             */
/*   Updated: 2026/01/27 00:05:30 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Freeing one `t_env` node */
void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

/* Freeing the `t_env` list */
void	free_env_list(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free_env_node(head);
		head = tmp;
	}
}
