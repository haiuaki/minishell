/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:02:54 by juljin            #+#    #+#             */
/*   Updated: 2026/01/27 14:20:45 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `export` */
void	bi_export(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("export %s%c\"%s\"\n", tmp->key, '=', tmp->value);
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
	bi_export(env_copy);
	return (0);
}
*/