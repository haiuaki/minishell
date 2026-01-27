/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:11:15 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:49 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex_count(unsigned long nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 16;
		count++;
	}
	return (count);
}

void	hex_init(unsigned long nbr, t_flags *f, int *hexlen, int *hexprefix)
{
	*hexlen = hex_count(nbr);
	*hexprefix = 0;
	if (f->hash && nbr != 0)
		*hexprefix = 2;
	if (f->dot && f->precision > *hexlen)
		*hexlen = f->precision;
	if (f->dot && f->precision == 0 && nbr == 0)
		*hexlen = 0;
}

int	hex_width(int hexlen, int hexfix, t_flags *f)
{
	if (f->width > (hexlen + hexfix))
		return (f->width - hexlen - hexfix);
	return (0);
}

int	hex_padding(int hexlen, int hexfix, t_flags *f)
{
	int	padding;
	int	i;

	if (!f)
		return (0);
	padding = hex_width(hexlen, hexfix, f);
	i = 0;
	while (i < padding)
	{
		write(1, " ", 1);
		i++;
	}
	return (padding);
}

int	hex_zero_padding(int hexlen, int hexfix, t_flags *f)
{
	int	padding;
	int	i;

	padding = hex_width(hexlen, hexfix, f);
	i = 0;
	while (i < padding)
	{
		write(1, "0", 1);
		i++;
	}
	return (padding);
}
