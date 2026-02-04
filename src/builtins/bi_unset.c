/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:27:18 by juljin            #+#    #+#             */
/*   Updated: 2026/01/27 17:58:31 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `unset` */
void	bi_unset(char *key_str, t_env **head_ptr)
{
	t_env	*tmp;
	t_env	*prev;

	if (!key_str)
		return ;
	while (*key_str && ft_isspace(*key_str))
		key_str++;
	if (!*key_str)
		return ;
	tmp = *head_ptr;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key_str) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*head_ptr = tmp->next;
			free_env_node(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
/*
int	main(int ac, char *av[], char *envp[])
{
	t_env	*env_copy;
	t_env	*new_node;

	(void)ac;
	(void)av;
	env_copy = copy_env(envp);
	if (!env_copy)
		return (1);
	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup("HELLO");
	new_node->value = NULL;
	new_node->next = NULL;
	printf("\n/////////////////// [BEFORE DELETION] ///////////////////\n");
	env_add_back(&env_copy, new_node);
	bi_env(env_copy);
	bi_unset("OLDPWD", &env_copy);
	printf("\n/////////////////// [AFTER DELETION] ///////////////////\n");
	bi_env(env_copy);
	return (0);
}
*/