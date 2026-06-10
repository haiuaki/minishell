/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 09:09:17 by juljin            #+#    #+#             */
/*   Updated: 2026/06/10 10:32:11 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Executes a segment starting at 'start'.
 * If it's a pipeline (multiple commands connected by TK_PIPE), uses
 * exec_multiple. Otherwise, uses exec_single_coms.
 * Returns pointer to the last command in the executed segment.
 */
static t_cmd	*exec_segment(t_shell *s, t_cmd *start)
{
	t_cmd	*saved_cmds;
	t_cmd	*segment_end;
	int		is_pipeline;

	is_pipeline = (start->bonus.connector == TK_PIPE);
	segment_end = start;
	while (segment_end && segment_end->bonus.connector == TK_PIPE)
		segment_end = segment_end->next;
	saved_cmds = s->cmds;
	s->cmds = start;
	if (is_pipeline)
		exec_multiple(s);
	else
		exec_single_coms(s);
	s->cmds = saved_cmds;
	if (!segment_end)
		return (start);
	return (segment_end);
}

/*
 * Executes a list of commands, handling logical operators (&& and ||).
 * It iterates through command "segments" (pipelines or single commands).
 * Before executing a segment, it checks the exit code and connector of the
 * previous segment to determine if the current segment should be skipped,
 * correctly propagating the logical flow.
 */
void	exec_command_list(t_shell *s)
{
	t_cmd	*current;
	t_cmd	*last_in_segment;
	t_cmd	*segment_end;

	current = s->cmds;
	last_in_segment = NULL;
	while (current)
	{
		if (last_in_segment
			&& ((last_in_segment->bonus.connector == TK_AND
					&& s->last_exit_code != 0)
				|| (last_in_segment->bonus.connector == TK_OR
					&& s->last_exit_code == 0)))
		{
			segment_end = current;
			while (segment_end->next && segment_end->bonus.connector == TK_PIPE)
				segment_end = segment_end->next;
			last_in_segment = segment_end;
			current = segment_end->next;
			continue ;
		}
		last_in_segment = exec_segment(s, current);
		current = last_in_segment->next;
	}
}
