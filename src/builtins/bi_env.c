/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:39:41 by juljin            #+#    #+#             */
/*   Updated: 2026/03/26 13:06:47 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `env` */
void	bi_env(t_shell *s, t_cmd *cmd)
{
	t_env	*env_curr;

	s->last_exit_code = 0;
	if (cmd->args[1])
	{
		s->last_exit_code = 1;
		print_error("minishell: env", "", "too many arguments");
		return ;
	}
	env_curr = s->env_list;
	env_set_value(s->env_list, "_", "/usr/bin/env");
	while (env_curr)
	{
		if (env_curr->is_exported && env_curr->value)
		{
			ft_putstr_fd(env_curr->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(env_curr->value, 1);
		}
		env_curr = env_curr->next;
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
