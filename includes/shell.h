/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:12:17 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 18:38:30 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/* ---------------------------------- MAIN ---------------------------------- */

int		init_shell_struct(t_shell **s, char *envp[]);
int		setup_shell(t_shell **s, int ac, char *envp[]);
void	update_before_next_input(t_shell *s);

/* ------------------------------- SHELL LOOP ------------------------------- */

// Input handling
void	prepare_for_input(t_shell *s);
char	*read_input(t_shell *s);
int		handle_signal(t_shell *s);
int		complete_input_loop(t_shell *s);
int		process_input(t_shell *s);

// Command execution
void	process_commands(t_shell *s);

/* -------------------------------- CLEANUP --------------------------------- */

void	free_shell_struct(t_shell *s);

#endif
