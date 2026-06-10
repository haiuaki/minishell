/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:03:51 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 18:01:23 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Reads one continuation line ("> ") with dedicated signal handling.
 * Backs up and restores STDIN because SIGINT handler closes it to interrupt
 * readline immediately.
 * (Only restore STDIN via `dup2` if a signal was received,
 * preventing an inherited file descriptor at exit when exiting
 * because of `Ctrl+D` (130))
 */
static char	*read_continuation_line(t_shell *s)
{
	char	*next_line;
	int		stdin_backup;

	if (!s->is_interactive)
		return (get_next_line(STDIN_FILENO, 0));
	sig_set_block_input();
	stdin_backup = dup(STDIN_FILENO);
	g_signal = 0;
	next_line = readline("> ");
	if (stdin_backup >= 0)
	{
		if (g_signal != 0)
			dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	sig_set_parent();
	return (next_line);
}

/* 
 * If `next_line` isn't empty (""), appends a whitespace (" ")
 * to the initial input before completing the input with the newly read line.
 * Frees the initial input and the newly read line.
 * If the line is empty, just free the read line.
 */
static void	append_line(t_shell *s, char *next_line)
{
	char	*old_input;
	char	*tmp;

	if (next_line[0])
	{
		old_input = s->input;
		tmp = ft_strjoin(old_input, " ");
		s->input = ft_strjoin(tmp, next_line);
		free(old_input);
		free(tmp);
	}
	free(next_line);
}

/* 
 * Helper function to handle Ctrl+D (EOF)
 * Prints the syntax error message and exits the program cleanly,
 * by freeing the centralized `t_shell` struct with the status code 2.
 */
static void	handle_eof_and_exit(t_shell *s)
{
	print_error("minishell: syntax error", "", "unexpected end of file");
	if (s->is_interactive)
		ft_putendl_fd("exit", STDERR_FILENO);
	free_shell_struct(s);
	exit(2);
}

/*
 * Completes the incomplete input.
 * If the incomplete input was given to the program through a script,
 * reads the next line from STDIN.
 * If the incomplete input is given in a terminal,
 * reads the next input with "> "
 * - Ctrl+D exits the shell, with a status code of 2. (!next_line check)
 * - Ctrl+C exits the interactive mode to complete the input. (g_signal check)
 * - Ctrl+\ does nothing.
 */
int	complete_input_loop(t_shell *s)
{
	char	*next_line;

	while (is_incomplete(s->tokens))
	{
		next_line = read_continuation_line(s);
		if (g_signal)
		{
			add_history(s->input);
			free(next_line);
			return (0);
		}
		if (!next_line)
			handle_eof_and_exit(s);
		append_line(s, next_line);
		add_history(s->input);
		free_token_list(s->tokens);
		s->tokens = tokenizer(s->input);
		if (!handle_op_error(s, s->tokens))
			return (0);
	}
	return (1);
}
