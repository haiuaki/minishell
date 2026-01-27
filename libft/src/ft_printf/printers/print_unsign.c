/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:33:38 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:15:03 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	unsign_width(unsigned int nbr, t_flags *f)
{
	int	unsignlen;

	unsignlen = unsign_count(nbr);
	if (f->dot && f->precision > unsignlen)
		unsignlen = f->precision;
	if (f->dot && f->precision == 0 && nbr == 0)
		unsignlen = 0;
	if (f->width > unsignlen)
		return (f->width - unsignlen);
	return (0);
}
// if f->width <= unsignlen, no padding needed so return 0

static int	unsign_padding(unsigned int nbr, t_flags *f)
{
	int	padding;
	int	i;

	padding = unsign_width(nbr, f);
	i = 0;
	while (i < padding)
	{
		write(1, " ", 1);
		i++;
	}
	return (padding);
}

static int	unsign_zero_padding(unsigned int nbr, t_flags *f)
{
	int	padding;
	int	i;

	padding = unsign_width(nbr, f);
	i = 0;
	while (i < padding)
	{
		write(1, "0", 1);
		i++;
	}
	return (padding);
}

static int	unsign_precision(unsigned int nbr, t_flags *f)
{
	int	padding;
	int	i;

	padding = f->precision - unsign_count(nbr);
	i = 0;
	while (i < padding)
	{
		write(1, "0", 1);
		i++;
	}
	return (padding);
}

int	print_unsign(unsigned int nbr, t_flags *f)
{
	int	count;
	int	padding;
	int	unsignlen;

	if (!f)
		return (unsign_recursive(nbr));
	count = 0;
	unsignlen = unsign_count(nbr);
	if (f->dot && f->precision > unsignlen)
		unsignlen = f->precision;
	padding = unsign_width(nbr, f);
	if (!f->hyphen && padding > 0 && (!f->zero || f->dot))
		count += unsign_padding(nbr, f);
	if (!f->hyphen && padding > 0 && f->zero && !f->dot)
		count += unsign_zero_padding(nbr, f);
	if (f->dot && f->precision > unsign_count(nbr))
		count += unsign_precision(nbr, f);
	if (!(f->dot && f->precision == 0 && nbr == 0))
		count += unsign_recursive(nbr);
	if (f->hyphen && padding > 0)
		count += unsign_padding(nbr, f);
	return (count);
}
