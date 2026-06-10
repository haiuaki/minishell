/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_close_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:35:00 by juljin            #+#    #+#             */
/*   Updated: 2026/06/10 10:32:30 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Closes all redirect file descriptors for a single command. */
void	close_redir_fds(t_cmd *cmd)
{
	t_redir	*tmp;

	if (!cmd)
		return ;
	if (cmd->bonus.subshell)
		close_all_redir_fds(cmd->bonus.subshell);
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->fd_heredoc >= 0)
		{
			close(tmp->fd_heredoc);
			tmp->fd_heredoc = -1;
		}
		if (tmp->fd_open >= 0)
		{
			close(tmp->fd_open);
			tmp->fd_open = -1;
		}
		tmp = tmp->next;
	}
}

/* Closes heredoc and open file descriptors for a redirection. */
static void	close_fds(t_redir *redir)
{
	if (redir->fd_heredoc >= 0)
	{
		close(redir->fd_heredoc);
		redir->fd_heredoc = -1;
	}
	if (redir->fd_open >= 0)
	{
		close(redir->fd_open);
		redir->fd_open = -1;
	}
}

/* Closes file descriptors that do not belong to the current command. */
void	close_outside_fds(t_cmd *current_cmd, t_cmd *cmd_head)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd_head;
	while (tmp)
	{
		if (tmp != current_cmd)
		{
			if (tmp->bonus.subshell)
				close_all_redir_fds(tmp->bonus.subshell);
			redir = tmp->redir;
			while (redir)
			{
				close_fds(redir);
				redir = redir->next;
			}
		}
		tmp = tmp->next;
	}
}

/* Closes all redirection file descriptors from all commands in the pipeline. */
void	close_all_redir_fds(t_cmd *cmd_head)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmd_head;
	while (cmd)
	{
		if (cmd->bonus.subshell)
			close_all_redir_fds(cmd->bonus.subshell);
		if (cmd->redir)
		{
			redir = cmd->redir;
			while (redir)
			{
				close_fds(redir);
				redir = redir->next;
			}
		}
		cmd = cmd->next;
	}
}
