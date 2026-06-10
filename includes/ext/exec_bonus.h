/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:20:29 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/07 02:40:59 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BONUS_H
# define EXEC_BONUS_H

# include "structs.h"

/* ------------------------------- EXECUTION -------------------------------- */

void	exec_single_coms(t_shell *s);
void	exec_multiple(t_shell *s);
void	exec_external_cmd(t_shell *s);
void	exec_subshell(t_shell *s, t_cmd *cmd);
void	child_process(t_shell *s, t_pipe *data);
void	child_process_exec(t_shell *s, t_pipe *data, char *cmd_path,
			char **env_array);
void	exec_command_list(t_shell *s);

/* -------------------------------- PIPELINE -------------------------------- */

int		exec_loop(t_shell *s, t_pipe *data);

/* -------------------------------- HERE-DOC -------------------------------- */

int		init_here_doc(t_shell *s);
void	read_here_doc_lines(t_shell *s, int write_fd, t_redir *redir);
int		null_line(char *line, char *delimiter);

/* -------------------------------- BUILTINS -------------------------------- */

void	single_bi(t_shell *s);
void	exec_builtins(t_shell *s);
int		is_builtin(t_cmd *cmd);
int		no_output_bi(t_cmd *cmd);

/* ------------------------------ REDIRECTIONS ------------------------------ */

int		apply_redir(t_cmd *cmd);
int		apply_redir_no_cmd(t_cmd *cmd);
void	apply_all_redir(t_shell *s, t_pipe *data, char **env_array,
			char *cmd_path);
int		default_redir(t_cmd *cmd, t_pipe *data);
void	prepare_pipeline_redir(t_cmd *cmd);
int		open_target(t_redir *redir);
void	close_redir_fds(t_cmd *cmd);
void	close_outside_fds(t_cmd *current_cmd, t_cmd *cmd_head);
void	close_all_redir_fds(t_cmd *cmd_head);

/* --------------------------------- UTILS ---------------------------------- */

char	*get_path(char *cmd, char *envp[]);
int		is_dir(const char *path);
void	update_underscore_var(t_shell *s);

/* ------------------------------ ERROR & EXIT ------------------------------ */

void	handle_path_error(t_shell *s, t_pipe *data, char **env_array);
void	exit_child(t_shell *s, char **env_array, char *cmd_path,
			int code);

/* -------------------------------- CLEANUP --------------------------------- */

void	free_cmd_list(t_cmd *cmd);
void	free_cmd_node(t_cmd *node_cmd);
void	free_redir_list(t_redir *redir);
void	free_redir_node(t_redir *redir_node);
void	cleanup_exec_resources(char *cmd_path, char **env_array);

/* ----------------------------- PIPELINE UTILS ----------------------------- */

int		child_builtins(t_shell *s, t_pipe *data, char **env_array,
			t_cmd *current_cmd);
void	handle_subshell(t_shell *s, char **env_array,
			char *cmd_path);
void	handle_empty_cmd(t_shell *s, t_pipe *data, char **env_array);
void	init_pipe_data(t_shell *s, t_pipe *data);

#endif
