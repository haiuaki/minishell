/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:19:33 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 18:35:01 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to free the allocated memory in the `t_shell` struct */
void	free_shell_struct(t_shell *s)
{
	if (s->input)
		free(s->input);
	if (s->tokens)
		free_token_list(s->tokens);
	if (s->head_cmds)
		free_cmd_list(s->head_cmds);
	else if (s->cmds)
		free_cmd_list(s->cmds);
	if (s->env_list)
		free_env_list(s->env_list);
	get_next_line(0, 1);
	free(s);
}

/* 
 * Initializes the `t_shell` struct containing all the global datas of the
 * program. Copies the environment and checks if the program is connected
 * to a terminal.
 */
int	init_shell_struct(t_shell **s, char *envp[])
{
	*s = ft_calloc(1, sizeof(t_shell));
	if (!*s)
		return (0);
	(*s)->env_list = copy_env(envp);
	if (!(*s)->env_list)
	{
		(*s)->env_list = minimal_env();
		if (!(*s)->env_list)
			return (free(*s), 0);
	}
	(*s)->is_interactive = isatty(STDIN_FILENO);
	(*s)->is_first_cmd = 1;
	return (1);
}

/* Initializes the shell: usage, struct, environment, SHLVL and signals */
int	setup_shell(t_shell **s, int ac, char *envp[])
{
	if (ac != 1)
		return (printf(USAGE), 0);
	if (!init_shell_struct(s, envp))
		return (0);
	handle_shlvl(*s);
	if (!(*s)->is_interactive)
		sig_set_default();
	return (1);
}

/* 
 * Frees the previous input and the `t_token` list.
 * If the given input was the first executed command, sets the 
 * `is_first_cmd` to 0 for tracking.
 */
void	update_before_next_input(t_shell *s)
{
	free(s->input);
	free_token_list(s->tokens);
	if (s->is_first_cmd)
		s->is_first_cmd = 0;
}
