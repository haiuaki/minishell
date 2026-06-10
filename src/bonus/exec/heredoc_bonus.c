/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:55:38 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/13 18:05:00 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Creates a pipe and reads heredoc content into it.
 * The content is read from STDIN until the delimiter is found.
 * Delimiter is used as-is (never expanded), but content is expanded
 * unless delimiter was quoted.
 * Returns the read end of pipe containing the heredoc content
 * or -1 on error.
 * Write end is closed after reading; read end stays open for exec.
 */
static int	here_doc(t_shell *s, t_redir *redir)
{
	int	fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		return (-1);
	if (redir->redir_target)
	{
		read_here_doc_lines(s, fd_here_doc[1], redir);
	}
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}

/* 
 * Processes all heredocs for a single command,
 * recursively handling subshells
 */
static int	process_cmd_heredocs(t_shell *s, t_cmd *cmd)
{
	t_redir	*tmp_redir;
	t_shell	subshell_state;

	if (cmd->bonus.is_subshell)
	{
		subshell_state = *s;
		subshell_state.cmds = cmd->bonus.subshell;
		if (init_here_doc(&subshell_state) == -1)
			return (-1);
	}
	tmp_redir = cmd->redir;
	while (tmp_redir)
	{
		if (tmp_redir->type == TK_HEREDOC)
		{
			tmp_redir->fd_heredoc = here_doc(s, tmp_redir);
			if (tmp_redir->fd_heredoc == -1)
				return (-1);
		}
		tmp_redir = tmp_redir->next;
	}
	return (0);
}

/*
 * Initializes all heredocs in the command pipeline BEFORE execution.
 * Iterates through all commands and all redirections.
 * Creates pipe and reads content for each << heredoc found.
 * Handles signal handling (Ctrl+C) to exit cleanly.
 * Returns 0 on success, -1 if pipe creation fails.
 * Recursively handles heredocs within subshells.
 */
int	init_here_doc(t_shell *s)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = s->cmds;
	while (tmp_cmd)
	{
		if (process_cmd_heredocs(s, tmp_cmd) == -1)
			return (-1);
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
