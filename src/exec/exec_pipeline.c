/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:27:52 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/13 17:27:42 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Executes built-in commands in a child process if applicable. */
static int	child_builtins(t_shell *s, t_pipe *data, char **env_array,
	t_cmd *current_cmd)
{
	int	exit_code;

	if (!current_cmd->args || !current_cmd->args[0])
	{
		s->cmds = data->cmd_head;
		exit_child(s, env_array, NULL, 0);
	}
	if (is_builtin(current_cmd))
	{
		ft_free_array(env_array);
		exec_builtins(s);
		s->cmds = data->cmd_head;
		exit_code = s->last_exit_code;
		exit_child(s, NULL, NULL, exit_code);
	}
	return (0);
}

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

/* Prepares the environment and redirections for a child process. */
void	child_process(t_shell *s, t_pipe *data)
{
	char	**env_array;
	char	*cmd_path;
	t_cmd	*current_cmd;

	sig_set_default();
	cmd_path = NULL;
	current_cmd = s->cmds;
	env_array = env_to_array(data->env);
	if (!env_array)
	{
		s->cmds = data->cmd_head;
		exit_child(s, NULL, NULL, 1);
	}
	close_outside_fds(current_cmd, data->cmd_head);
	apply_all_redir(s, data, env_array, cmd_path);
	if (!current_cmd->args || !current_cmd->args[0])
	{
		s->cmds = data->cmd_head;
		exit_child(s, env_array, NULL, 0);
	}
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
	if (s->cmds->next)
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

	data->cmd_index = 0;
	data->prev_read_pipe = -1;
	data->cmd_head = s->cmds;
	data->env = s->env_list;
	data->tokens = s->tokens;
	current = s->cmds;
	prepare_pipeline_redir(current);
	while (current)
	{
		s->cmds = current;
		if (current->next)
		{
			if (pipe(data->pipe_fd) == -1)
				return (print_error("minishell: ", "pipe",
						strerror(errno)), -1);
		}
		parent_process(s, data);
		data->cmd_index++;
		current = current->next;
	}
	return (0);
}
