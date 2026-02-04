/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:13:52 by juljin            #+#    #+#             */
/*   Updated: 2026/01/26 17:54:12 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "sig.h"

/* -------------------------------- MESSAGES -------------------------------- */

# define USAGE		"Usage: ./minishell\n"
# define PROMPT		"minishell$ "

/* ---------------------------- GLOBAL VARIABLE ----------------------------- */

extern volatile sig_atomic_t	g_signal;

#endif