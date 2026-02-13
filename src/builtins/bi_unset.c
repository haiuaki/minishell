/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:27:18 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 17:55:10 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Helper function to check every node inside the `t_env` list
 * to see if one of the given arguments to `unset` matches an existing variable.
 */
static void	unset_key_loop(t_token *token, t_env **head_ptr, t_env *tmp,
		t_env *prev)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->key, token->value) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*head_ptr = tmp->next;
			free_env_node(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/*
 * Helper function that splits the given arguments into an array
 * and then searches the `t_env` list with `unset_key_loop()
 * to see if it can be unset.
 */
static void	unset_args(t_token *token, t_env **head_ptr)
{
	t_env	*prev;
	t_env	*tmp;
	size_t	i;

	i = 0;
	if (!token)
		return ;
	while (token)
	{
		tmp = *head_ptr;
		prev = NULL;
		unset_key_loop(token, head_ptr, tmp, prev);
		i++;
		token = token->next;
	}
}

/* Implementation of the built-in command `unset` */
void	bi_unset(t_token *token, t_env **head_ptr)
{
	if (token && ft_strcmp(token->value, "unset") == 0)
		token = token->next;
	if (!token->value)
		return ;
	unset_args(token, head_ptr);
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