/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:06:23 by juljin            #+#    #+#             */
/*   Updated: 2026/06/10 11:15:00 by jlnjin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
 * This file contains all the core data structure definitions for minishell.
 * It is included by all other header files to prevent circular dependencies.
 */

# include <stddef.h>	// For size_t
# include <sys/types.h>
# include "types.h"
# include "bonus.h"

/* ------------------------------- ENV STRUCT ------------------------------- */

struct s_env
{
	char			*key;
	char			*value;
	int				is_exported;
	int				empty_start;
	struct s_env	*next;
};

/* ----------------------------- LEXER STRUCTS ------------------------------ */

struct s_token
{
	char			*value;
	char			*meta;
	t_token_type	type;
	struct s_token	*next;
	int				to_skip;
};

struct s_tokenizer
{
	const char	*input;
	char		*buffer;
	char		*meta_buffer;
	size_t		read_i;
	size_t		write_i;
	char		quote_char;
	int			complete;
};

/* ------------------------------ EXEC STRUCTS ------------------------------ */

struct s_redir
{
	t_token_type	type;
	char			*redir_target;
	int				fd_target;
	int				fd_heredoc;
	int				fd_open;
	int				quoted_delimiter;
	struct s_redir	*next;
};

struct s_cmd
{
	char			**args;
	t_redir			*redir;
	int				redir_error;
	t_cmd_bonus		bonus;
	struct s_cmd	*next;
};

struct s_pipe
{
	int		pipe_fd[2];
	int		prev_read_pipe;
	pid_t	pid;
	int		status;
	int		cmd_index;
	t_cmd	*cmd_head;
	t_env	*env;
	t_token	*tokens;
};

/* ------------------------------ SHELL STRUCT ------------------------------ */

struct s_shell
{
	char	*input;
	t_env	*env_list;
	t_token	*tokens;
	t_cmd	*cmds;
	t_cmd	*head_cmds;
	int		last_exit_code;
	int		is_first_cmd;
	int		is_interactive;
};

#endif
