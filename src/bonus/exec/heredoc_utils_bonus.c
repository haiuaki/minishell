/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:42:34 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 11:42:36 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if readline returned NULL (EOF or SIGINT)
 * Prints warning if EOF encountered without signal (user didn't type delimiter)
 * Returns 1 if line is NULL, 0 otherwise.
 */
int	null_line(char *line, char *delimiter)
{
	char	*error_msg;
	char	*tmp;

	if (!line)
	{
		if (g_signal == 0)
		{
			tmp = ft_strjoin("here-document (wanted `", delimiter);
			error_msg = ft_strjoin(tmp, "')");
			free(tmp);
			print_error("minishell: warning", "", error_msg);
			free(error_msg);
		}
		return (1);
	}
	return (0);
}

/*
 * Writes heredoc line to the pipe write end.
 * Expands variables in content if delimiter was unquoted.
 */
static void	write_heredoc_line(t_shell *s, int fd, char *line, int quoted)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_heredoc_string(s, line);
		ft_putstr_fd(expanded, fd);
		free(expanded);
	}
	else
		ft_putstr_fd(line, fd);
}

/*
 * Reads heredoc input line by line until delimiter is found.
 * Writes each line to the pipe write end.
 * Stops on delimiter match, NULL input (EOF) or signal interrupt (SIGINT).
 */
void	read_here_doc_lines(t_shell *s, int write_fd, t_redir *redir)
{
	char	*line;

	while (1)
	{
		if (s->is_interactive)
			line = readline("> ");
		else
			line = get_next_line(0, 0);
		if (null_line(line, redir->redir_target))
			break ;
		if (ft_strcmp(line, redir->redir_target) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(s, write_fd, line, redir->quoted_delimiter);
		if (s->is_interactive)
			ft_putstr_fd("\n", write_fd);
		free(line);
	}
}
