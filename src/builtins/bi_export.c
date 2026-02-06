/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:02:54 by juljin            #+#    #+#             */
/*   Updated: 2026/02/06 18:29:01 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Helper funciton to print the error message the given argument doesn't
 * have a key (e.g. `=VALUE`)
 */
static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

/*
 * Helper function to verify if the environment variable already exists.
 * Returns 1 if it already exists and replaces the value of the variable
 * by the new given value.
 * Returns 0 if it doesn't, it will add the variable to the list.
 */
static int	does_exist(t_env **head_ptr, t_env *node)
{
	t_env	*tmp;

	tmp = *head_ptr;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, node->key) == 0)
		{
			tmp->is_exported = 1;
			if (node->value != NULL)
			{
				tmp->value = ft_strdup(node->value);
				if (!tmp->value)
					free(tmp->value);
			}
			free_env_node(node);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
 * Helper function to handle arguments and add to the `t_env` list.
 * (e.g. `export a=1 b=2 c=3)
 */
static int	export_args(char **args, t_env **head_ptr)
{
	t_env	*node;
	t_env	*tmp;
	size_t	i;

	tmp = *head_ptr;
	i = 0;
	while (args[i])
	{
		node = env_new_node(args[i]);
		if (!node)
		{
			print_export_error(args[i]);
			i++;
			continue ;
		}
		if (!does_exist(&tmp, node))
		{
			if (node->value != NULL)
				node->is_exported = 1;
			env_add_back(head_ptr, node);
		}
		i++;
	}
	return (ft_free_array(args), 1);
}

/*
 * Implementation of the built-in command `export`
 * If no argument is given, it writes the list of exported variables
 * in a format suitable for re-input to the shell.
 */
void	bi_export(char *str, t_env **head_ptr)
{
	char	**args;
	t_env	*tmp;

	tmp = *head_ptr;
	args = ft_split(str, ' ');
	if (!args)
		return (ft_free_array(args));
	if (args[0] != NULL)
		export_args(args, head_ptr);
	else
	{
		while (tmp)
		{
			if (tmp->value == NULL)
				printf("export %s\n", tmp->key);
			else
				printf("export %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
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