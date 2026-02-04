/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:28:29 by juljin            #+#    #+#             */
/*   Updated: 2026/01/26 18:30:44 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SIGINT signal handler (exit code 128 + 2) */
static void	sigint_handler(sig_atomic_t signal)
{
	g_signal = 128 + signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
 * This function sets the default behaviour when X signal is received
 * in interactive mode:
 * Ctrl+C displays a new prompt on a new line.
 * Ctrl+D exits the shell.
 * Ctrl+\ does nothing.
 */
void	sig_set_parent(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sa_int, NULL);
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
 * This function sets the default behaviour when X signal is received
 * in non-interactive mode:
 * Ctrl+C sends SIGINT, ends the executing command and exit to shell.
 * Ctrl+D sends an EOF to STDIN. Does nothing if the process doesn't read STDIN.
 * Ctrl+\ sends SIGQUIT, force quits and dumps core.
 */
void	sig_set_default(void)
{
	struct sigaction	sa_default;

	ft_bzero(&sa_default, sizeof(sa_default));
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sa_default.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}
