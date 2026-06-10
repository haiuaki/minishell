/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:30:11 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/14 11:58:10 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Finds the matching closing parenthesis for a given opening parenthesis.
 * Returns the token pointer to the matching TK_RPAREN, or NULL if not found.
 */
static t_token	*find_matching_paren(t_token *open_paren)
{
	t_token	*current;
	int		depth;

	if (!open_paren || open_paren->type != TK_LPAREN)
		return (NULL);
	depth = 1;
	current = open_paren->next;
	while (current && depth > 0)
	{
		if (current->type == TK_LPAREN)
			depth++;
		else if (current->type == TK_RPAREN)
			depth--;
		if (depth == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/* 
 * Handles subshell creation and parsing.
 * Sets the current pointer to the token following the subshell.
 * Returns the created command node, or NULL on error.
 */
static t_cmd	*parse_subshell(t_token **current, t_cmd **head)
{
	t_token	*match;
	t_token	*next_after;
	t_cmd	*cmds;

	match = find_matching_paren(*current);
	if (!match)
		return (NULL);
	cmds = ft_calloc(1, sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->bonus.is_subshell = 1;
	next_after = match->next;
	match->next = NULL;
	cmds->bonus.subshell = get_cmd((*current)->next);
	match->next = next_after;
	cmds->redir = get_redir(match->next);
	cmd_add_back(head, cmds);
	*current = match->next;
	while (*current && !is_logical_connector(*current)
		&& ((*current)->type == TK_WORD || is_operator(*current)))
		*current = (*current)->next;
	return (cmds);
}

/* 
 * Handles simple command creation and parsing.
 * Sets the current pointer to the next connector or end of list.
 * Returns the created command node, or NULL on error.
 */
static t_cmd	*parse_simple_command(t_token **current, t_cmd **head)
{
	t_cmd	*cmds;

	cmds = create_cmd_struct(*current);
	if (!cmds)
		return (NULL);
	cmd_add_back(head, cmds);
	while (*current && !is_logical_connector(*current))
		*current = (*current)->next;
	return (cmds);
}

/* 
 * Parses the token list into a linked list of command structures
 * Splits the token stream by connector operators (|, &&, ||) and creates
 * a `t_cmd` node for each command segment.
 * Handles subshells recursively.
 */
t_cmd	*get_cmd(t_token *token)
{
	t_token	*current;
	t_cmd	*head;
	t_cmd	*cmds;

	current = token;
	head = NULL;
	while (current)
	{
		if (current->type == TK_LPAREN)
			cmds = parse_subshell(&current, &head);
		else
			cmds = parse_simple_command(&current, &head);
		if (!cmds)
			return (free_cmd_list(head), NULL);
		if (current && (current->type == TK_PIPE
				|| current->type == TK_AND || current->type == TK_OR))
		{
			cmds->bonus.connector = current->type;
			current = current->next;
		}
		else if (current && current->type == TK_RPAREN)
			current = current->next;
	}
	return (head);
}
