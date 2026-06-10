/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:52 by juljin            #+#    #+#             */
/*   Updated: 2026/06/10 16:49:34 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------- FOUNDATIONAL HEADERS -------------------------- */

# include "includes.h"
# include "libft.h"
# include "structs.h"

/* --------------------------- SUBSYSTEM HEADERS ---------------------------- */

# include "builtins.h"
# include "env.h"
# include "error.h"
# include "exec.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "shell.h"
# include "sig.h"

/* -------------------------------- MESSAGES -------------------------------- */

# define USAGE		"Usage: ./minishell\n"
# define PROMPT		"minishell$ "

/* ---------------------------- GLOBAL VARIABLE ----------------------------- */

extern volatile sig_atomic_t	g_signal;

#endif
