/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:17:00 by juljin            #+#    #+#             */
/*   Updated: 2026/04/10 09:26:06 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Identifies the command path and executes it using execve. */
void	child_process_exec(t_shell *s, t_pipe *data, char *cmd_path,
				char **env_array)
{
	t_cmd	*current_cmd;

	current_cmd = s->cmds;
	if (child_builtins(s, data, env_array, current_cmd))
		return ;
	cmd_path = get_path(current_cmd->args[0], env_array);
	if (!cmd_path)
		handle_path_error(s, data, env_array);
	if (is_dir(cmd_path))
	{
		s->cmds = data->cmd_head;
		print_error("minishell: ", current_cmd->args[0], "Is a directory");
		exit_child(s, env_array, cmd_path, 126);
	}
	execve(cmd_path, current_cmd->args, env_array);
	perror("execve");
	s->cmds = data->cmd_head;
	exit_child(s, env_array, cmd_path, 127);
}

/* Prepares the environment and redirections for a child process, 
   handling subshells and empty commands. */
void	child_process(t_shell *s, t_pipe *data)
{
	char	**env_array;
	char	*cmd_path;

	sig_set_default();
	cmd_path = NULL;
	env_array = env_to_array(data->env);
	if (!env_array)
	{
		s->cmds = data->cmd_head;
		exit_child(s, NULL, NULL, 1);
	}
	close_outside_fds(s->cmds, data->cmd_head);
	apply_all_redir(s, data, env_array, cmd_path);
	handle_subshell(s, env_array, cmd_path);
	handle_empty_cmd(s, data, env_array);
	child_process_exec(s, data, cmd_path, env_array);
}

/* Forks a child process and handles pipe file descriptors in the parent. */
static void	parent_process(t_shell *s, t_pipe *data)
{
	data->pid = fork();
	if (data->pid == -1)
		return (print_error("minishell: ", "fork", strerror(errno)));
	if (data->pid == 0)
		child_process(s, data);
	close_redir_fds(s->cmds);
	if (data->prev_read_pipe != -1)
		close(data->prev_read_pipe);
	if (s->cmds->bonus.connector == TK_PIPE)
	{
		close(data->pipe_fd[1]);
		data->prev_read_pipe = data->pipe_fd[0];
	}
	else
		data->prev_read_pipe = -1;
}

/* Iterates through the command list and manages the pipeline execution. */
int	exec_loop(t_shell *s, t_pipe *data)
{
	t_cmd	*current;
	t_cmd	*prev;

	init_pipe_data(s, data);
	current = s->cmds;
	prepare_pipeline_redir(current);
	while (current)
	{
		s->cmds = current;
		if (current->bonus.connector == TK_PIPE)
		{
			if (pipe(data->pipe_fd) == -1)
				return (print_error("minishell: ", "pipe",
						strerror(errno)), -1);
		}
		parent_process(s, data);
		data->cmd_index++;
		prev = current;
		current = current->next;
		if (prev->bonus.connector != TK_PIPE)
			break ;
	}
	return (0);
}
