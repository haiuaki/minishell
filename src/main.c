/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:58:50 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 18:35:09 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

/* Core run loop of the minishell program */
static void	shell_loop(t_shell *s)
{
	while (1)
	{
		prepare_for_input(s);
		s->input = read_input(s);
		if (handle_signal(s))
			continue ;
		if (!s->input)
		{
			if (s->is_interactive)
				ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (!process_input(s))
		{
			update_before_next_input(s);
			continue ;
		}
		process_commands(s);
		update_before_next_input(s);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_shell	*s;
	int		exit_code;

	(void)av;
	if (!setup_shell(&s, ac, envp))
		return (1);
	shell_loop(s);
	exit_code = s->last_exit_code;
	free_shell_struct(s);
	return (exit_code);
}
