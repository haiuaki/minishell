/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:02:54 by juljin            #+#    #+#             */
/*   Updated: 2026/02/06 14:45:19 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			tmp->value = ft_strdup(node->value);
			if (!tmp->value)
				free(tmp->value);
			free_env_node(node);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
 * Implementation of the built-in command `export`
 * If no argument is given, it writes the list of exported variables
 * in a format suitable for re-input to the shell.
 */
void	bi_export(char *str, t_env **head_ptr)
{
	t_env	*tmp;
	t_env	*node;

	tmp = *head_ptr;
	while (*str && ft_isspace(*str))
		str++;
	if (*str)
	{
		node = env_new_node(str);
		if (!node)
			return (free_env_list(*head_ptr));
		if (!does_exist(&tmp, node))
			env_add_back(head_ptr, node);
	}
	else
	{
		while (tmp)
		{
			printf("export %s%c\"%s\"\n", tmp->key, '=', tmp->value);
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