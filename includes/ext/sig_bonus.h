/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:05:05 by juljin            #+#    #+#             */
/*   Updated: 2026/04/07 02:42:48 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_BONUS_H
# define SIG_BONUS_H

# include "includes.h"

/* ----------------------------- SIGNAL HANDLERS ---------------------------- */

void	sigint_handler(sig_atomic_t signal);
void	sigint_input_handler(sig_atomic_t signal);
void	sigint_exec_handler(sig_atomic_t signal);
void	sigquit_exec_handler(sig_atomic_t signal);

/* ----------------------------- SIGNAL SETTERS ----------------------------- */

void	sig_set_default(void);
void	sig_set_parent(void);
void	sig_set_exec_parent(void);
void	sig_set_block_input(void);

#endif
