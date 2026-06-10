/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 08:52:14 by juljin            #+#    #+#             */
/*   Updated: 2026/04/13 16:45:00 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if a string contains an unquoted wildcard character (*) */
static int	has_wildcard(char *str, char *meta)
{
	size_t	i;

	if (!str || !meta)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && meta[i] == 'N')
			return (1);
		i++;
	}
	return (0);
}

/* Converts the sorted array of strings into a linked list of t_token nodes */
static t_token	*matches_to_token_list(char **matches, size_t count,
	t_token *original)
{
	t_token	*head;
	t_token	*curr;
	t_token	*new;
	size_t	i;

	head = NULL;
	curr = NULL;
	i = 0;
	while (i < count)
	{
		new = create_match_token(matches[i], original);
		if (!new)
			return (free_token_list(head), NULL);
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		i++;
	}
	return (head);
}

/* Get all matching files for the wildcard pattern */
static t_token	*get_matching_files(char *pattern, t_token *original)
{
	char	**matches;
	size_t	count;
	t_token	*head;

	matches = collect_matching_names(pattern, &count);
	if (!matches || count == 0)
	{
		free_matches_array(matches, count);
		return (NULL);
	}
	sort_matches(matches, count);
	head = matches_to_token_list(matches, count, original);
	free_matches_array(matches, count);
	return (head);
}

/* Replace a wildcard token with expanded matches */
static void	expand_wildcard_token(t_token **prev, t_token **current,
	t_token **head)
{
	t_token	*matches;
	t_token	*last_match;
	t_token	*old_token;

	matches = get_matching_files((*current)->value, *current);
	if (!matches)
	{
		*prev = *current;
		*current = (*current)->next;
		return ;
	}
	old_token = *current;
	last_match = matches;
	while (last_match->next)
		last_match = last_match->next;
	last_match->next = old_token->next;
	if (*prev)
		(*prev)->next = matches;
	else
		*head = matches;
	*current = last_match->next;
	*prev = last_match;
	free_token_node(old_token);
}

/* Main wildcard expansion function. Iterates and expands wildcards. */
void	expand_wildcards(t_token **tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == TK_WORD && has_wildcard(current->value,
				current->meta))
			expand_wildcard_token(&prev, &current, tokens);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
