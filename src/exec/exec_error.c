/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:40:31 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/13 17:56:45 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees all inherited heap and exits with the given code. */
void	exit_child(t_shell *s, char **env_array, char *cmd_path, int code)
{
	if (env_array)
		ft_free_array(env_array);
	if (cmd_path)
		free(cmd_path);
	if (s)
		free_shell_struct(s);
	exit(code);
}

/* Resets command list head, cleans up resources, and exits. */
static void	exit_handler(t_shell *s, t_pipe *data, char **env, int exit_code)
{
	if (data)
		s->cmds = data->cmd_head;
	cleanup_exec_resources(NULL, env);
	exit_child(s, NULL, NULL, exit_code);
}

/* Handles errors related to command path existence and permissions. */
void	handle_path_error(t_shell *s, t_pipe *data, char **env_array)
{
	struct stat	sb;
	char		*cmd_name;

	cmd_name = s->cmds->args[0];
	if (ft_strchr(cmd_name, '/') && stat(cmd_name, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			print_error("minishell: ", cmd_name, "Is a directory");
		else
			print_error("minishell: ", cmd_name, "Permission denied");
		exit_handler(s, data, env_array, 126);
	}
	else
	{
		if (ft_strchr(cmd_name, '/'))
			print_error("minishell: ", cmd_name, strerror(errno));
		else
			print_error("minishell: ", cmd_name, "command not found");
		exit_handler(s, data, env_array, 127);
	}
}
