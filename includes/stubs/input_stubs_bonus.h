/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stubs_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 12:00:00 by jlnjin            #+#    #+#             */
/*   Updated: 2026/06/09 12:00:00 by jlnjin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STUBS_BONUS_H
# define INPUT_STUBS_BONUS_H

typedef struct s_token	t_token;
int	is_incomplete_mandatory(t_token *tokens);

/* Mandatory version of the incomplete input check */
static inline int	is_incomplete(t_token *tokens)
{
	return (is_incomplete_mandatory(tokens));
}

#endif
