/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:16:34 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/10 10:30:41 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Executes an external command in a child process. */
static void	child_external(t_shell *s)
{
	char	**env_array;
	char	*cmd_path;

	env_array = env_to_array(s->env_list);
	if (!env_array)
		return ;
	if (!s->cmds->args || !s->cmds->args[0])
		return (exit_child(s, env_array, NULL, 0));
	cmd_path = get_path(s->cmds->args[0], env_array);
	if (!apply_redir(s->cmds))
	{
		cleanup_exec_resources(cmd_path, env_array);
		return (exit_child(s, NULL, NULL, 1));
	}
	if (!cmd_path)
		handle_path_error(s, NULL, env_array);
	if (is_dir(cmd_path))
	{
		print_error("minishell: ", s->cmds->args[0], "Is a directory");
		cleanup_exec_resources(cmd_path, env_array);
		return (exit_child(s, NULL, NULL, 126));
	}
	execve(cmd_path, s->cmds->args, env_array);
	perror("execve");
	exit_child(s, env_array, cmd_path, 127);
}

/* Handles process status and sets exit code */
static void	handle_child_status(t_shell *s, int status)
{
	if (WIFEXITED(status))
		s->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		s->last_exit_code = 128 + WTERMSIG(status);
}

/* Forks and manages the execution of an external command. */
void	exec_external_cmd(t_shell *s)
{
	pid_t	pid;
	int		status;

	status = 0;
	sig_set_exec_parent();
	pid = fork();
	if (pid == -1)
	{
		sig_set_parent();
		return (print_error("minishell: ", "fork", strerror(errno)));
	}
	if (pid == 0)
		child_external(s);
	if (waitpid(pid, &status, 0) != -1)
		handle_child_status(s, status);
	sig_set_parent();
}

/* Executes a builtin command in a child process for redirection. */
static void	child_bi(t_shell *s)
{
	if (!apply_redir(s->cmds))
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		if (s->head_cmds)
			free_cmd_list(s->head_cmds);
		else
			free_cmd_list(s->cmds);
		free_token_list(s->tokens);
		free_env_list(s->env_list);
		free(s);
		exit(1);
	}
	exec_builtins(s);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (s->head_cmds)
		free_cmd_list(s->head_cmds);
	else
		free_cmd_list(s->cmds);
	free_token_list(s->tokens);
	free_env_list(s->env_list);
	free(s);
	exit(0);
}

/* Manages the execution of a single builtin command. */
void	single_bi(t_shell *s)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!s->cmds->redir)
		return (exec_builtins(s));
	if (no_output_bi(s->cmds))
	{
		if (!apply_redir_no_cmd(s->cmds))
			s->last_exit_code = 1;
		else
			exec_builtins(s);
		return ;
	}
	sig_set_exec_parent();
	pid = fork();
	if (pid == -1)
	{
		sig_set_parent();
		return (print_error("minishell: ", "fork", strerror(errno)));
	}
	if (pid == 0)
		child_bi(s);
	if (waitpid(pid, &status, 0) != -1)
		handle_child_status(s, status);
}
