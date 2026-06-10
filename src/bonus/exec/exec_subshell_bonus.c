/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:42:07 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 11:42:09 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Executes a subshell in a child process, handling redirections. */
static void	child_subshell(t_shell *s, t_cmd *cmd)
{
	int		exit_code;

	if (!apply_redir(cmd))
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_shell_struct(s);
		exit(1);
	}
	s->cmds = cmd->bonus.subshell;
	exec_command_list(s);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit_code = s->last_exit_code;
	free_shell_struct(s);
	exit(exit_code);
}

/* Forks and manages the execution of a subshell. */
void	exec_subshell(t_shell *s, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (print_error("minishell: ", "fork", strerror(errno)));
	if (pid == 0)
		child_subshell(s, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		s->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		s->last_exit_code = 128 + WTERMSIG(status);
}
