/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:57:58 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/13 17:55:15 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Executes a single command, either builtin or external. */
void	exec_single_coms(t_shell *s)
{
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
