/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:12:55 by juljin            #+#    #+#             */
/*   Updated: 2026/03/13 09:03:33 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Verifies if the `OLDPWD` variable exists.
 * If not, manually adds it to the `t_env` list as an exported variable
 * without a set value.
 * This is necessary in case the program is ran in `bash` without prior `cd`
 * commands or manual value assignment to `OLDPWD`.
 * The *envp[] argument in the `main` function does not contain the
 * variables without values.
 */
static int	manual_oldpwd(t_env **head)
{
	t_env	*new_node;

	if (env_var_exists(*head, "OLDPWD"))
		return (1);
	new_node = env_new_node("OLDPWD");
	if (!new_node)
		return (0);
	new_node->is_exported = 1;
	env_add_back(head, new_node);
	return (1);
}

/* Copying the `char *envp[]` from the system into a linked list */
t_env	*copy_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	size_t	i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = env_new_node(envp[i]);
		if (!new_node)
			return (free_env_list(head), NULL);
		new_node->is_exported = 1;
		env_add_back(&head, new_node);
		i++;
	}
	if (envp && *envp)
	{
		if (!manual_oldpwd(&head))
			return (free_env_list(head), NULL);
	}
	return (head);
}
/*
int	main(int ac, char *av[], char *envp[])
{
	t_env	*env_copy;

	(void)ac;
	(void)av;
	env_copy = copy_env(envp);
	if (!env_copy)
		return (1);
	while (env_copy)
	{
		printf("Key: %s\n", env_copy->key);
		printf("Value: %s\n", env_copy->value);
		printf("Exported: %d\n", env_copy->is_exported);
		env_copy = env_copy->next;
	}
	return (0);
}
*/
