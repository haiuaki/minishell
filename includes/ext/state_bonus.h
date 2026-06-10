/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:00:00 by jlnjin            #+#    #+#             */
/*   Updated: 2026/06/10 11:00:00 by jlnjin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_BONUS_H
# define STATE_BONUS_H

# include "types.h"

typedef struct s_cmd_bonus
{
	t_token_type	connector;
	int				is_subshell;
	struct s_cmd	*subshell;
}	t_cmd_bonus;

#endif
