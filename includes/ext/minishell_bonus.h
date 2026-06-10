/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:52 by juljin            #+#    #+#             */
/*   Updated: 2026/04/07 02:41:06 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

/* -------------------------- FOUNDATIONAL HEADERS -------------------------- */

# include "includes.h"
# include "libft.h"
# include "structs.h"

/* --------------------------- SUBSYSTEM HEADERS ---------------------------- */

# include "builtins_bonus.h"
# include "env_bonus.h"
# include "error_bonus.h"
# include "exec_bonus.h"
# include "expander_bonus.h"
# include "lexer_bonus.h"
# include "parser_bonus.h"
# include "shell_bonus.h"
# include "sig_bonus.h"

/* -------------------------------- MESSAGES -------------------------------- */

# define USAGE		"Usage: ./minishell\n"
# define PROMPT		"minishell$ "

/* ---------------------------- GLOBAL VARIABLE ----------------------------- */

extern volatile sig_atomic_t	g_signal;

#endif
