/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:41:59 by juljin            #+#    #+#             */
/*   Updated: 2026/03/06 11:16:36 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees a `t_token` node */
void	free_token_node(t_token *node)
{
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	if (node->meta)
		free(node->meta);
	free(node);
}

/* Frees a `t_token` list */
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
