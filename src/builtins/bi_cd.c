/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:41:26 by juljin            #+#    #+#             */
/*   Updated: 2026/03/23 13:35:45 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Searches for the `HOME` variable in the `t_env` list.
 * If not found, returns an error message and sets the exit code to 1.
 */
static char	*retrieve_home(t_shell *s)
{
	char	*home_path;

	home_path = env_get_value(s->env_list, "HOME");
	if (!home_path)
	{
		print_error("minishell", "cd", "HOME not set");
		s->last_exit_code = 1;
		return (NULL);
	}
	return (home_path);
}

/*
 * Retrieves the parent directory of the current directory.
 * This function is used if the current directory has no permission,
 * which will make `getcwd()` fail when running `cd ..`.
 * It retrieves the previously saved `PWD` from the `t_env` list
 * and finds the last slash and replaces it with a '\0' to cut
 * the no permission directory.
 * Handles directories under root (e.g. "/no_perm" -> "/")
 */
static char	*get_parent_path(t_shell *s)
{
	char	*pwd;
	char	*parent;
	char	*last_slash;

	pwd = env_get_value(s->env_list, "PWD");
	if (!pwd)
		return (NULL);
	parent = ft_strdup(pwd);
	if (!parent)
		return (NULL);
	if (ft_strcmp(parent, "/") == 0)
		return (parent);
	last_slash = ft_strrchr(parent, '/');
	if (last_slash == parent)
		parent[1] = '\0';
	else if (last_slash)
		*last_slash = '\0';
	return (parent);
}

/*
 * Helper function to update the `t_env` variables `PWD` and `OLDPWD`
 * Handle errors, sets the `last_exit_code` to 1 in case `getcwd` fails
 * (e.g.: orphaned directory, no permission directory)
 * Frees the allocated arrays after updating the values with `env_set_value`.
 */
static void	free_and_update_pwd(t_shell *s, char *old_pwd_save,
					char *parent_path)
{
	char	*new_pwd;

	if (parent_path)
		free(parent_path);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_error("chdir: error retrieving current directory: ",
			"getcwd: cannot access parent directories", strerror(errno));
		if (old_pwd_save)
			free(old_pwd_save);
		s->last_exit_code = 1;
		return ;
	}
	env_set_value(s->env_list, "PWD", new_pwd);
	free(new_pwd);
	if (old_pwd_save)
	{
		env_set_value(s->env_list, "OLDPWD", old_pwd_save);
		free(old_pwd_save);
	}
}

/*
 * Checks the arguments given to the `cd` function.
 * Handle errors and special cases like no argument or if `~` is given.
 * Returns the target value.
 */
static char	*set_target(t_shell *s, t_cmd *cmd)
{
	char	*target;

	if (cmd->args[1] && cmd->args[2])
	{
		s->last_exit_code = 1;
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
	{
		target = retrieve_home(s);
		if (!target)
			return (NULL);
	}
	else
		target = cmd->args[1];
	return (target);
}

/*
 * Implementation of the builtin command `cd` with relative and absolute paths.
 * Handles orphaned directories or with no permissions.
 */
void	bi_cd(t_shell *s, t_cmd *cmd)
{
	char	*old_pwd_save;
	char	*target;
	char	*parent_path;

	s->last_exit_code = 0;
	parent_path = NULL;
	target = set_target(s, cmd);
	if (!target)
		return ;
	old_pwd_save = getcwd(NULL, 0);
	if (ft_strcmp(target, "..") == 0 && !old_pwd_save)
	{
		parent_path = get_parent_path(s);
		if (parent_path)
			target = parent_path;
	}
	if (!old_pwd_save)
		old_pwd_save = ft_strdup(env_get_value(s->env_list, "PWD"));
	if (chdir(target) == -1)
		return (handle_chdir_error(s, cmd->args[1],
				old_pwd_save, parent_path));
	if (parent_path || !cmd->args[1])
		free(target);
	free_and_update_pwd(s, old_pwd_save, parent_path);
}
