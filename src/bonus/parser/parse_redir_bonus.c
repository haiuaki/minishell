/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:59:38 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/10 09:49:06 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if heredoc delimiter contains any quotes */
static int	has_quoted_delimiter(char *meta)
{
	int	i;

	i = 0;
	while (meta[i])
	{
		if (meta[i] == '\'' || meta[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

/* Creates and initializes a single redirection structure */
static t_redir	*create_redir(t_token *token)
{
	t_redir	*redir;

	if (!token || !token->next)
		return (NULL);
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (token->type == TK_HEREDOC || token->type == TK_REDIR_IN)
		redir->fd_target = STDIN_FILENO;
	else if (token->type == TK_APPEND || token->type == TK_REDIR_OUT)
		redir->fd_target = STDOUT_FILENO;
	redir->redir_target = ft_strdup(token->next->value);
	if (!redir->redir_target)
		return (free(redir), NULL);
	redir->quoted_delimiter = has_quoted_delimiter(token->next->meta);
	redir->fd_heredoc = -1;
	redir->fd_open = -1;
	redir->type = token->type;
	redir->next = NULL;
	return (redir);
}

/* Appends a redirection node to the end of the redirection linked list */
void	redir_add_back(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!head || !new_redir)
		return ;
	if (!(*head))
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

/* 
 * Parses tokens and builds a linked list of all redirections for a command
 * Scans tokens until a logical connector is found and extracts all redirection 
 * operators.
 * Each operator must be followed by a TK_WORD.
 * Redirections are stored in order of appearance.
 */
t_redir	*get_redir(t_token *token)
{
	t_redir	*head;
	t_redir	*redir;
	t_token	*current;

	if (!token)
		return (NULL);
	head = NULL;
	current = token;
	while (current)
	{
		if (is_logical_connector(current))
			break ;
		if (current->next && (current->type == TK_APPEND
				|| current->type == TK_HEREDOC || current->type == TK_REDIR_IN
				|| current->type == TK_REDIR_OUT)
			&& current->next->type == TK_WORD)
		{
			redir = create_redir(current);
			if (!redir)
				return (free_redir_list(head), NULL);
			redir_add_back(&head, redir);
		}
		current = current->next;
	}
	return (head);
}
