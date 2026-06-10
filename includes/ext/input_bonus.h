/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 12:00:00 by jlnjin            #+#    #+#             */
/*   Updated: 2026/06/09 12:00:00 by jlnjin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_BONUS_H
# define INPUT_BONUS_H

typedef struct s_token	t_token;
int	is_unclosed_paren(t_token *tokens);
int	is_incomplete_token(t_token *tokens);

/* Bonus version of the incomplete input check */
static inline int	is_incomplete(t_token *tokens)
{
	return (is_incomplete_token(tokens) || is_unclosed_paren(tokens));
}

#endif
