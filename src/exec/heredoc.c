/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:55:38 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/14 18:00:47 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if readline returned NULL (EOF or SIGINT)
 * Prints warning if EOF encountered without signal (user didn't type delimiter)
 * Returns 1 if line is NULL, 0 otherwise.
 */
static int	null_line(char *line, char *delimiter)
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
static void	read_here_doc_lines(t_shell *s, int write_fd, t_redir *redir)
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

/*
 * Creates a pipe and reads heredoc content into it.
 * The content is read from STDIN until the delimiter is found.
 * Delimiter is used as-is (never expanded), but content is expanded
 * unless delimiter was quoted.
 * Returns the read end of pipe containing the heredoc content
 * or -1 on error.
 * Write end is closed after reading; read end stays open for exec.
 */
static int	here_doc(t_shell *s, t_redir *redir)
{
	int	fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		return (-1);
	if (redir->redir_target)
		read_here_doc_lines(s, fd_here_doc[1], redir);
	close(fd_here_doc[1]);
	return (fd_here_doc[0]);
}

/*
 * Initializes all heredocs in the command pipeline BEFORE execution.
 * Iterates through all commands and all redirections.
 * Creates pipe and reads content for each << heredoc found.
 * Handles signal handling (Ctrl+C) to exit cleanly.
 * Returns 0 on success, -1 if pipe creation fails.
 */
int	init_here_doc(t_shell *s)
{
	t_redir	*tmp_redir;
	t_cmd	*tmp_cmd;

	tmp_cmd = s->cmds;
	tmp_redir = s->cmds->redir;
	while (tmp_cmd)
	{
		tmp_redir = tmp_cmd->redir;
		while (tmp_redir)
		{
			if (tmp_redir->type == TK_HEREDOC)
			{
				tmp_redir->fd_heredoc = here_doc(s, tmp_redir);
				if (tmp_redir->fd_heredoc == -1)
					return (-1);
			}
			tmp_redir = tmp_redir->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}
