/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:56:48 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 17:10:48 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SIGINT signal handler (exit code 128 + 2) */
void	sigint_handler(sig_atomic_t signal)
{
	g_signal = 128 + signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* SIGINT handler for blocking input (e.g. heredoc or continuation prompt) */
void	sigint_input_handler(sig_atomic_t signal)
{
	g_signal = 128 + signal;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

/* SIGINT handler for execution parent */
void	sigint_exec_handler(sig_atomic_t signal)
{
	(void)signal;
	g_signal = 128 + SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

/* SIGQUIT handler for execution parent (e.g.: `cat` with no argument)*/
void	sigquit_exec_handler(sig_atomic_t signal)
{
	(void)signal;
	g_signal = 128 + SIGQUIT;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}
