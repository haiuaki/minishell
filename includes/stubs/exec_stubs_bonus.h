/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stubs_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 12:00:00 by jlnjin            #+#    #+#             */
/*   Updated: 2026/06/09 12:00:00 by jlnjin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STUBS_BONUS_H
# define EXEC_STUBS_BONUS_H

typedef struct s_shell	t_shell;
void	exec_mandatory_list(t_shell *s);

/* Mandatory version of the command list execution */
static inline void	exec_command_list(t_shell *s)
{
	exec_mandatory_list(s);
}

#endif
