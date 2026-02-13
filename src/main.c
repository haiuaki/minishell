/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:58:50 by juljin            #+#    #+#             */
/*   Updated: 2026/02/05 17:39:38 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;
/*
int	main(int ac, char *av[], char *envp[])
{
	t_shell	data;
	char	*input;

	(void)av;
	if (ac != 1)
		return (printf(USAGE), 1);
	data.env = copy_env(envp);
	if (!data.env)
		return (1);
	while (1)
	{
		sig_set_parent();
		input = readline(PROMPT);
		if (!input)
			break ;
		if (input && *input)
			add_history(input);
		free(input);
	}
	free_env_list(data.env);
	return (0);
}
*/
