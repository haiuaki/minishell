/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:22:48 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/02 15:51:46 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Helper function for `export` and `unset`
 * Verifies the format of the variable's key.
 * It needs to be alphanumeric (e.g. key_variable=VALUE, `_` is accepted.)
 */
int	key_isalnum(char *key)
{
	size_t	i;

	i = 0;
	while (key[i])
	{
		if (ft_isdigit(key[0]) || (!ft_isalnum(key[i]) && key[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}
