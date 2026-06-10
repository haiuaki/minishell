/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:54:41 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/02 12:10:15 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if the command exists in the given paths. */
static char	*test_path(char *cmd, char **split_path)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			return (free(tmp), NULL);
		free(tmp);
		if (cmd_path && access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

/* Retrieves the full path of a command. */
char	*get_path(char *cmd, char *envp[])
{
	char	**split_path;
	char	*cmd_path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp || !envp[i])
		return (NULL);
	split_path = ft_split(envp[i] + 5, ':');
	if (!split_path)
		return (NULL);
	cmd_path = test_path(cmd, split_path);
	ft_free_array(split_path);
	return (cmd_path);
}

/* Checks if a command is a shell builtin. */
int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], ":") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "!") == 0)
		return (1);
	return (0);
}

/* Checks if a builtin command produces no standard output. */
int	no_output_bi(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0
		|| ft_strcmp(cmd->args[0], "export") == 0
		|| ft_strcmp(cmd->args[0], "unset") == 0
		|| ft_strcmp(cmd->args[0], "exit") == 0
		|| ft_strcmp(cmd->args[0], ":") == 0
		|| ft_strcmp(cmd->args[0], "!") == 0)
		return (1);
	return (0);
}

/* Checks if the given path is a directory. */
int	is_dir(const char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0 && S_ISDIR(s.st_mode))
		return (1);
	return (0);
}
