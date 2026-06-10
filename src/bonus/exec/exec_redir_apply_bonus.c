/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_apply_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:35:00 by juljin            #+#    #+#             */
/*   Updated: 2026/04/07 20:39:09 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Sets up standard input and output redirections for pipes. */
int	default_redir(t_cmd *cmd, t_pipe *data)
{
	if (!cmd)
		return (0);
	if (data->cmd_index > 0)
	{
		if (dup2(data->prev_read_pipe, STDIN_FILENO) == -1)
			return (0);
		close(data->prev_read_pipe);
	}
	if (cmd->bonus.connector == TK_PIPE)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
			return (0);
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
	}
	return (1);
}

/* Closes file descriptors that have been applied to standard streams. */
static void	close_applied_fds(t_redir *redir)
{
	if (redir->type == TK_HEREDOC)
	{
		close(redir->fd_heredoc);
		redir->fd_heredoc = -1;
	}
	else if (redir->fd_open >= 0)
	{
		close(redir->fd_open);
		redir->fd_open = -1;
	}
}

/* Applies all redirections for a specific command. */
int	apply_redir(t_cmd *cmd)
{
	t_redir		*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->fd_open == -1)
			tmp->fd_open = open_target(tmp);
		if (tmp->fd_open == -1)
			return (print_error("minishell: ", tmp->redir_target,
					strerror(errno)), 0);
		if (dup2(tmp->fd_open, tmp->fd_target) == -1)
			return (0);
		close_applied_fds(tmp);
		tmp = tmp->next;
	}
	return (1);
}

/* Opens and closes redirection targets when no command is present. */
int	apply_redir_no_cmd(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redir;
	while (tmp)
	{
		fd = open_target(tmp);
		if (fd == -1)
			return (print_error("minishell: ", tmp->redir_target,
					strerror(errno)), 0);
		if (tmp->type == TK_HEREDOC)
			tmp->fd_heredoc = -1;
		close(fd);
		tmp = tmp->next;
	}
	return (1);
}

/* Orchestrates the application of all redirections for the current command. */
void	apply_all_redir(t_shell *s, t_pipe *data, char **env_array,
			char *cmd_path)
{
	if (!default_redir(s->cmds, data))
	{
		s->cmds = data->cmd_head;
		exit_child(s, env_array, NULL, 1);
	}
	if (s->cmds->redir_error)
	{
		s->cmds = data->cmd_head;
		exit_child(s, env_array, NULL, 1);
	}
	if (!apply_redir(s->cmds))
	{
		s->cmds = data->cmd_head;
		cleanup_exec_resources(cmd_path, env_array);
		exit_child(s, NULL, NULL, 1);
		return ;
	}
}
