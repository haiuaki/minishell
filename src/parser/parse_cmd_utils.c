/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:22:49 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/01 12:42:04 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates and intializes a single command structure from tokens */
t_cmd	*create_cmd_struct(t_token *token)
{
	t_cmd	*cmds;

	cmds = ft_calloc(1, sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->args = tokens_to_argv(token);
	cmds->redir = get_redir(token);
	cmds->redir_error = 0;
	cmds->next = NULL;
	return (cmds);
}

/* Appends a command node to the end of the command linked list */
void	cmd_add_back(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!(*head))
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

/* Counts the number of command nodes in the linked list */
size_t	cmd_list_size(t_cmd *head)
{
	t_cmd	*current;
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

/* Evaluates if a token is completely unquoted and empty */
int	is_empty_unquoted(t_token *current)
{
	size_t	i;

	if (current->value[0] != '\0')
		return (0);
	if (current->meta[0] == '\0')
		return (0);
	i = 0;
	while (current->meta[i])
	{
		if (current->meta[i] != 'N')
			return (0);
		i++;
	}
	return (1);
}
