/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:30:11 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/01 12:40:24 by juljin           ###   ########.fr       */
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
char	**allocate_argv_array(t_token *token)
{
	char	**res;

	res = malloc(sizeof(char *) * (count_word_tokens(token) + 1));
	if (!res)
		return (NULL);
	return (res);
}

/* 
 * Converts only TK_WORDS to an array of strings for execve()
 * Skips redirection targets, empty strings and stops at pipe operators.
 * NULL-terminates the array.
 * Returns the allocated string array, or NULL on allocation failure.
 */
char	**tokens_to_argv(t_token *token)
{
	t_token	*current;
	size_t	i;
	char	**res;

	res = allocate_argv_array(token);
	i = 0;
	current = token;
	while (current)
	{
		if (current->next && current->type == TK_PIPE)
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

/* 
 * Parses the token list into a linked list of command structures
 * Splits the token stream by pipe operators (|) and creates a `t_cmd`
 * node for each command segment.
 * Each node contains : args: argv array for the command
 * and redir: linked list of redirections
 * Returns head of the command list, or NULL on failure.
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
		cmds = create_cmd_struct(current);
		if (!cmds)
			return (free_cmd_list(head), NULL);
		cmd_add_back(&head, cmds);
		while (current && current->type != TK_PIPE)
			current = current->next;
		if (current && current->type == TK_PIPE)
			current = current->next;
	}
	return (head);
}
/* 
int	main(int ac, char *av[], char *envp[])
{
	t_env	*env;
	t_token	*tokens;
	char	*input;
	t_cmd	*cmd;
	t_cmd	*tmp;
	size_t	i;
	size_t	j;

	(void)ac;
	(void)av;
	env = copy_env(envp);
	while (1)
	{
		j = 0;
		i = 0;
		tokens = NULL;
		input = readline(PROMPT);
		if (!input)
			return (1);
		if (input && *input)
		{
			add_history(input);
			tokens = tokenizer(input);
			if (!tokens)
				return (free(input), free_env_list(env), 1);
			expander(&tokens, env);
		}
		cmd = get_cmd(tokens);
		tmp = cmd;
		while (tmp)
		{
			i = 0;
			while (tmp->args[i])
			{
				printf("cmds: %s\n", tmp->args[i]);
				i++;
			}
			if (tmp->redir)
			{
				printf("target: %s\n", tmp->redir->redir_target);
				printf("fd: %d\n", tmp->redir->fd_target);
			}
			tmp = tmp->next;
			j++;
		}
		printf("size of the cmd list: %zu\n", j);
		free_cmd_list(cmd);
		free_token_list(tokens);
		free(input);
	}
	free_env_list(env);
}
*/
