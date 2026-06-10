/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:28:29 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 17:15:08 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * This function sets signal handlers for parent process during execution:
 * Parent ignores SIGINT and SIGQUIT so only the child process receives them.
 * Used before fork() to protect the shell from being interrupted.
 */
void	sig_set_exec_parent(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_bzero(&sa_int, sizeof(sa_int));
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = &sigint_exec_handler;
	sigaction(SIGINT, &sa_int, NULL);
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = &sigquit_exec_handler;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
 * This function sets signal handlers for heredoc/continnuation prompt input:
 * Ctrl+C interrupts the input without exiting the shell
 * and without executing the command receiving the input.
 * Ctrl+\ is ignored.
 */
void	sig_set_block_input(void)
{
	struct sigaction	sa_heredoc;
	struct sigaction	sa_quit;

	ft_bzero(&sa_heredoc, sizeof(sa_heredoc));
	sigemptyset(&sa_heredoc.sa_mask);
	sa_heredoc.sa_flags = 0;
	sa_heredoc.sa_handler = &sigint_input_handler;
	sigaction(SIGINT, &sa_heredoc, NULL);
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
