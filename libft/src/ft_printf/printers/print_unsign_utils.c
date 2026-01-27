/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsign_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:51:45 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:15:05 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	unsign_count(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

int	unsign_recursive(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr > 9)
		count += unsign_recursive(nbr / 10);
	count += ft_putchar(nbr % 10 + '0');
	return (count);
}
