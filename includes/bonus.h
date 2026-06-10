/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:00:00 by jlnjin            #+#    #+#             */
/*   Updated: 2026/06/09 10:00:00 by jlnjin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# if defined(BONUS) && BONUS == 1

/* Full Bonus Features */
#  include "ext/state_bonus.h"
#  include "ext/input_bonus.h"

# else

/* Mandatory Stubs */
#  include "stubs/structs_stubs_bonus.h"
#  include "stubs/input_stubs_bonus.h"
#  include "stubs/exec_stubs_bonus.h"

# endif

#endif
