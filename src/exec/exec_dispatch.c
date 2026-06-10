/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:18:00 by juljin            #+#    #+#             */
/*   Updated: 2026/04/13 17:31:13 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Dispatches and executes shell builtin commands. */
void	exec_builtins(t_shell *s)
{
	char	*cmd;

	if (!s->cmds || !s->cmds->args || !s->cmds->args[0])
		return ;
	cmd = s->cmds->args[0];
	if (ft_strcmp(cmd, "cd") == 0)
		bi_cd(s, s->cmds);
	else if (ft_strcmp(cmd, "pwd") == 0)
		bi_pwd(s, s->cmds);
	else if (ft_strcmp(cmd, "echo") == 0)
		bi_echo(s, s->cmds);
	else if (ft_strcmp(cmd, "env") == 0)
		bi_env(s, s->cmds);
	else if (ft_strcmp(cmd, "exit") == 0)
		bi_exit(s, s->cmds);
	else if (ft_strcmp(cmd, "export") == 0)
		bi_export(s, s->cmds);
	else if (ft_strcmp(cmd, "unset") == 0)
		bi_unset(s, s->cmds);
	else if (ft_strcmp(cmd, ":") == 0)
		return ;
	else if (ft_strcmp(cmd, "!") == 0)
		return ;
}

/* Updates the "_" environment variable to the last command argument. */
void	update_underscore_var(t_shell *s)
{
	t_cmd	*last_cmd;
	char	**args;
	char	*last_arg;
	size_t	i;

	last_cmd = s->cmds;
	while (last_cmd && last_cmd->next)
		last_cmd = last_cmd->next;
	if (!last_cmd)
		return ;
	args = last_cmd->args;
	if (!args || !args[0])
		return ;
	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		last_arg = args[i - 1];
	else if (s->cmds->next != NULL)
		last_arg = "";
	else
		last_arg = args[0];
	env_set_value(s->env_list, "_", last_arg);
}
