/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:30:11 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/14 11:56:41 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * If the current token is a redirector, it sets the next token `to_skip` to 1.
 * This prevents the redirection filenames from appearing in the command argv.
 */
static void	skip_target_redir(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->next && is_operator(current))
			current->next->to_skip = 1;
		current = current->next;
	}
}

/* 
* Counts the number of valid word tokens for argv array allocation.
* Doesn't count empty strings, marked to_skip tokens.
* Calls `skip_target_redir` first to mark redirection targets.
* Stops at command separators (|, &&, ||) and parentheses.
*/
static size_t	count_word_tokens(t_token *token)
{
	t_token	*current;
	size_t	i;

	i = 0;
	current = token;
	skip_target_redir(current);
	current = token;
	while (current)
	{
		if (is_logical_connector(current))
			break ;
		if (current->type == TK_WORD && current->to_skip == 0
			&& !is_empty_unquoted(current))
			i++;
		current = current->next;
	}
	return (i);
}

/*
 * Allocates memory for argv array based on the word token count
 * (+1 for the NULL terminator).
 * Returns the allocated argv array.
 */
static char	**allocate_argv_array(t_token *token)
{
	char	**res;

	res = malloc(sizeof(char *) * (count_word_tokens(token) + 1));
	if (!res)
		return (NULL);
	return (res);
}

/* 
 * Converts only TK_WORDS to an array of strings for execve()
 * Skips redirection targets, empty strings and stops at connector operators.
 * NULL-terminates the array.
 * Returns the allocated string array, or NULL on allocation failure.
 */
char	**tokens_to_argv(t_token *token)
{
	t_token	*current;
	size_t	i;
	char	**res;

	res = allocate_argv_array(token);
	if (!res)
		return (NULL);
	i = 0;
	current = token;
	while (current)
	{
		if (is_logical_connector(current))
			break ;
		if (current->type == TK_WORD && current->to_skip == 0
			&& !is_empty_unquoted(current))
		{
			res[i] = ft_strdup(current->value);
			if (!res[i])
				return (ft_free_array(res), NULL);
			i++;
		}
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}
