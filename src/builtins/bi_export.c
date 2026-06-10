/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:02:54 by juljin            #+#    #+#             */
/*   Updated: 2026/03/26 17:59:35 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Helper function to verify if the environment variable already exists.
 * Returns 1 if it already exists and replaces the value of the variable
 * by the new given value.
 * Returns 0 if it doesn't, it will add the variable to the list.
 */
static int	does_exist(t_env *head, t_env *node)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, node->key) == 0)
		{
			current->is_exported = 1;
			if (node->value != NULL)
			{
				if (current->value)
					free(current->value);
				current->value = ft_strdup(node->value);
			}
			free_env_node(node);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

/*
 * Helper function to handle arguments and add to the `t_env` list.
 * (e.g. `export a=1 b=2 c=3)
 */
static int	export_args(t_shell *s, char **args)
{
	t_env	*node;
	int		i;

	if (!args)
		return (1);
	i = 0;
	while (args[i])
	{
		node = env_new_node(args[i]);
		if (!node || !key_isalnum(node->key))
		{
			free_env_node(node);
			print_key_error("export", args[i]);
			s->last_exit_code = 1;
			i++;
			continue ;
		}
		if (!does_exist(s->env_list, node))
		{
			node->is_exported = 1;
			env_add_back(&s->env_list, node);
		}
		i++;
	}
	return (1);
}

/* 
 * Prints the exported variables in the `t_env` list.
 * If the variable has not set value (e.g.: export a)
 * Or if it has a value (e.g.: export a="hello")
 */
static void	print_export(t_shell *s, t_env *env_curr)
{
	if (env_curr->value == NULL)
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putendl_fd(env_curr->key, STDOUT_FILENO);
	}
	else if (ft_strcmp(env_curr->key, "_") == 0 && !s->is_first_cmd)
		return ;
	else
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(env_curr->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(env_curr->value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
}

/*
 * Implementation of the built-in command `export`
 * If no argument is given, it writes the list of exported variables
 * in a format suitable for re-input to the shell.
 */
void	bi_export(t_shell *s, t_cmd *cmd)
{
	t_env	*sorted_env;
	t_env	*sorted_curr;

	s->last_exit_code = 0;
	if (cmd->args[1])
		export_args(s, &cmd->args[1]);
	else
	{
		sorted_env = get_sorted_env(s->env_list);
		if (!sorted_env)
			return ;
		sorted_curr = sorted_env;
		while (sorted_curr)
		{
			if (sorted_curr->is_exported)
				print_export(s, sorted_curr);
			sorted_curr = sorted_curr->next;
		}
		free_env_list(sorted_env);
	}
}
/*
int	main(int ac, char *av[], char *envp[])
{
	t_env	*env_copy;
	char	*input;

	(void)ac;
	(void)av;
	env_copy = copy_env(envp);
	if (!env_copy)
		return (1);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (!input && *input)
			add_history(input);
		if (ft_strncmp(input, "export", 6) == 0)
			bi_export(input + 6, &env_copy);
		if (ft_strcmp(input, "env") == 0)
			bi_env(env_copy);
		if (ft_strncmp(input, "unset", 5) == 0)
			bi_unset(input + 5, &env_copy);
		free(input);
	}
	free_env_list(env_copy);
	return (0);
}
 */
