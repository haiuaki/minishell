/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:03:21 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:53 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	nbr_abs(int nbr)
{
	if (nbr < 0)
		return (-(long)nbr);
	return ((long)nbr);
}

int	nbr_count(long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	nbr_sign(int nbr, t_flags *f)
{
	if (nbr < 0)
		return ('-');
	if (f->plus)
		return ('+');
	if (f->blank)
		return (' ');
	return ('\0');
}

int	nbr_recursive(int nbr)
{
	long	nb;
	int		count;

	nb = nbr_abs(nbr);
	count = 0;
	if (nbr < 0)
		count += ft_putchar('-');
	if (nb > 9)
		count += nbr_recursive(nb / 10);
	count += ft_putchar(nb % 10 + '0');
	return (count);
}

int	nbr_recursive_digits(long nb)
{
	int	count;

	count = 0;
	if (nb > 9)
		count += nbr_recursive_digits(nb / 10);
	count += ft_putchar(nb % 10 + '0');
	return (count);
}
