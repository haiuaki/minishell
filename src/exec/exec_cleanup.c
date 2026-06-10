/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:33:45 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/13 17:29:17 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees a `t_cmd` node */
void	free_cmd_node(t_cmd *node_cmd)
{
	if (!node_cmd)
		return ;
	if (node_cmd->args)
		ft_free_array(node_cmd->args);
	if (node_cmd->redir)
		free_redir_list(node_cmd->redir);
	free(node_cmd);
}

/* Frees a `t_cmd` list */
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*current;

	if (!cmd)
		return ;
	while (cmd)
	{
		current = cmd->next;
		free_cmd_node(cmd);
		cmd = current;
	}
}

/* Frees a `t_redir` node */
void	free_redir_node(t_redir *redir_node)
{
	if (!redir_node)
		return ;
	if (redir_node->fd_heredoc >= 0)
		close(redir_node->fd_heredoc);
	if (redir_node->fd_open >= 0)
		close(redir_node->fd_open);
	if (redir_node->redir_target)
		free(redir_node->redir_target);
	free(redir_node);
}

/* Frees a `t_redir` list */
void	free_redir_list(t_redir *redir)
{
	t_redir	*current;

	if (!redir)
		return ;
	while (redir)
	{
		current = redir->next;
		free_redir_node(redir);
		redir = current;
	}
}

/* Frees the command path and the environment array. */
void	cleanup_exec_resources(char *cmd_path, char **env_array)
{
	if (cmd_path)
		free(cmd_path);
	if (env_array)
		ft_free_array(env_array);
}
