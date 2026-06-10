/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:38:51 by juljin            #+#    #+#             */
/*   Updated: 2026/04/01 15:14:07 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Initializes heredocs and returns 1 if successful
 * 0 if interrupted by signal
 */
static int	setup_heredocs(t_shell *s)
{
	sig_set_block_input();
	g_signal = 0;
	init_here_doc(s);
	if (g_signal)
	{
		s->last_exit_code = g_signal;
		dup2(STDERR_FILENO, STDIN_FILENO);
		sig_set_parent();
		return (0);
	}
	return (1);
}

/* Parses tokens into commands and executes them */
void	process_commands(t_shell *s)
{
	s->cmds = get_cmd(s->tokens);
	s->head_cmds = s->cmds;
	if (!s->cmds)
		return ;
	if (setup_heredocs(s))
	{
		sig_set_exec_parent();
		exec_command_list(s);
		sig_set_parent();
		update_underscore_var(s);
	}
	free_cmd_list(s->cmds);
	s->head_cmds = NULL;
}

/* Executes the command list in mandatory mode (single or pipeline) */
void	exec_mandatory_list(t_shell *s)
{
	if (s->cmds->next == NULL)
		exec_single_coms(s);
	else
		exec_multiple(s);
}
