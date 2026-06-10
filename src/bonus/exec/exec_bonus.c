/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:15:00 by juljin            #+#    #+#             */
/*   Updated: 2026/04/06 21:37:26 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Executes a single command, either builtin, external or a subshell. */
void	exec_single_coms(t_shell *s)
{
	if (s->cmds->bonus.is_subshell)
	{
		exec_subshell(s, s->cmds);
		return ;
	}
	if (!s->cmds->args || !s->cmds->args[0])
	{
		if (s->cmds->redir)
			apply_redir_no_cmd(s->cmds);
		return ;
	}
	if (is_builtin(s->cmds))
		single_bi(s);
	else
		exec_external_cmd(s);
}

/* Executes multiple commands in a pipeline and waits for completion. */
void	exec_multiple(t_shell *s)
{
	t_pipe	data;

	if (exec_loop(s, &data) == -1)
		return ;
	s->cmds = data.cmd_head;
	if (data.prev_read_pipe != -1)
		close(data.prev_read_pipe);
	close_all_redir_fds(data.cmd_head);
	waitpid(data.pid, &data.status, 0);
	if (WIFEXITED(data.status))
		s->last_exit_code = WEXITSTATUS(data.status);
	else if (WIFSIGNALED(data.status))
		s->last_exit_code = 128 + WTERMSIG(data.status);
	while (wait(NULL) > 0)
		;
}
