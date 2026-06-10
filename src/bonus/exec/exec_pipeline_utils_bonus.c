/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:43:56 by juljin            #+#    #+#             */
/*   Updated: 2026/04/10 09:20:52 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Executes built-in commands in a child process if applicable. */
int	child_builtins(t_shell *s, t_pipe *data, char **env_array,
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

/*
 * Handles the execution of a subshell. 
 * If the current command is a subshell, this function sets the command list
 * to the subshell's command list and executes it. The child process then exits
 * with the subshell's exit code.
 */
void	handle_subshell(t_shell *s, char **env_array,
		char *cmd_path)
{
	if (s->cmds->bonus.is_subshell)
	{
		s->cmds = s->cmds->bonus.subshell;
		exec_command_list(s);
		exit_child(s, env_array, cmd_path, s->last_exit_code);
	}
}

/*
 * Handles the case of an empty command.
 * If the command has no arguments, the child process exits with status 0.
 */
void	handle_empty_cmd(t_shell *s, t_pipe *data, char **env_array)
{
	if (!s->cmds->args || !s->cmds->args[0])
	{
		s->cmds = data->cmd_head;
		exit_child(s, env_array, NULL, 0);
	}
}

/*
 * Initializes the pipe data structure.
 * Sets up the initial values for the command index, previous read pipe,
 * command head, environment list, and token list.
 */
void	init_pipe_data(t_shell *s, t_pipe *data)
{
	data->cmd_index = 0;
	data->prev_read_pipe = -1;
	data->cmd_head = s->cmds;
	data->env = s->env_list;
	data->tokens = s->tokens;
}
