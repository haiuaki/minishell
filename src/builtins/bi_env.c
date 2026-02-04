/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:39:41 by juljin            #+#    #+#             */
/*   Updated: 2026/01/27 14:20:38 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `env` */
void	bi_env(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s%c%s\n", tmp->key, '=', tmp->value);
		tmp = tmp->next;
	}
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
	bi_env(env_copy);
	return (0);
}
*/