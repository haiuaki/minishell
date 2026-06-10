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

/* ------------------------------- ENV STRUCT ------------------------------- */

struct s_env
{
	char			*key;
	char			*value;
	int				is_exported;
	int				empty_start;
	struct s_env	*next;
};

/* ------------------------------ SHELL STRUCT ------------------------------ */

struct s_shell
{
	char	*input;
	t_env	*env_list;
	void	*tokens;
	void	*cmds;
	void	*head_cmds;
	int		last_exit_code;
	int		is_first_cmd;
	int		is_interactive;
};

#endif
