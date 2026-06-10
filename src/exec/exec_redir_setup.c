/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:49:16 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/13 17:39:44 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Opens the target file for a specific redirection. */
int	open_target(t_redir *redir)
{
	int	fd;

	if (redir->fd_open >= 0)
		return (redir->fd_open);
	fd = -1;
	if (redir->type == TK_APPEND)
		fd = open(redir->redir_target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == TK_REDIR_IN)
		fd = open(redir->redir_target, O_RDONLY);
	else if (redir->type == TK_REDIR_OUT)
		fd = open(redir->redir_target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TK_HEREDOC)
		fd = redir->fd_heredoc;
	return (fd);
}

/* Opens all redirection targets for a single command. */
static int	prepare_cmd_redir(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type != TK_HEREDOC)
		{
			tmp->fd_open = open_target(tmp);
			if (tmp->fd_open == -1)
				return (print_error("minishell: ", tmp->redir_target,
						strerror(errno)), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

/* Recursively prepares redirections for all commands in the pipeline. */
void	prepare_pipeline_redir(t_cmd *cmd)
{
	if (!cmd)
		return ;
	prepare_pipeline_redir(cmd->next);
	if (cmd->redir && !prepare_cmd_redir(cmd))
		cmd->redir_error = 1;
}
