/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:13:59 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 18:00:00 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prepares the shell for the next input iteration */
void	prepare_for_input(t_shell *s)
{
	if (s->is_interactive)
		sig_set_parent();
	s->tokens = NULL;
	s->cmds = NULL;
}

/* Reads input from the appropriate source (interactive or script) */
char	*read_input(t_shell *s)
{
	if (s->is_interactive)
		return (readline(PROMPT));
	else
		return (get_next_line(0, 0));
}

/* Handles signal interruption and updates exit code */
int	handle_signal(t_shell *s)
{
	if (!g_signal)
		return (0);
	s->last_exit_code = g_signal;
	g_signal = 0;
	return (0);
}

/* 
 * Finalizes the input processing by expanding variables and 
 * performing a final syntax check.
 */
static int	finalize_input(t_shell *s)
{
	if (!s->tokens)
	{
		s->last_exit_code = 2;
		return (0);
	}
	expander(s);
	if (!handle_op_error(s, s->tokens))
	{
		free_token_list(s->tokens);
		s->tokens = NULL;
		return (0);
	}
	return (1);
}

/* 
 * Tokenizes and expands the input if not empty.
 * If the input ends with an incomplete pipeline, asks the user to complete it.
 * Properly appends the next line from STDIN to the initial input and add the
 * complete pipeline input to the command history.
 */
int	process_input(t_shell *s)
{
	if (!*s->input || ft_str_isspace(s->input))
		return (0);
	s->tokens = tokenizer(s->input);
	if (!handle_op_error(s, s->tokens))
	{
		add_history(s->input);
		free_token_list(s->tokens);
		s->tokens = NULL;
		return (0);
	}
	if (!complete_input_loop(s))
		return (0);
	add_history(s->input);
	return (finalize_input(s));
}
