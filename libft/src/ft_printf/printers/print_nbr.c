/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:54:35 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:51 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbr_width(int nbr, t_flags *f)
{
	int	nbrlen;
	int	signlen;

	nbrlen = nbr_count(nbr_abs(nbr));
	if (nbrlen == 0)
		nbrlen = 1;
	if (f->dot && f->precision > nbrlen)
		nbrlen = f->precision;
	if (f->dot && f->precision == 0 && nbr == 0)
		nbrlen = 0;
	if (nbr_sign(nbr, f) != '\0')
		signlen = 1;
	else
		signlen = 0;
	if (f->width > (nbrlen + signlen))
		return (f->width - nbrlen - signlen);
	return (0);
}

static int	nbr_padding(int nbr, t_flags *f)
{
	int	padding;
	int	i;

	padding = nbr_width(nbr, f);
	i = 0;
	while (i < padding)
	{
		write(1, " ", 1);
		i++;
	}
	return (padding);
}

static int	nbr_zero_padding(int nbr, t_flags *f)
{
	int	padding;
	int	i;

	padding = nbr_width(nbr, f);
	i = 0;
	while (i < padding)
	{
		write(1, "0", 1);
		i++;
	}
	return (padding);
}

static int	nbr_precision(long nb, t_flags *f)
{
	int	padding;
	int	i;

	padding = f->precision - nbr_count(nb);
	i = 0;
	while (i < padding)
	{
		write(1, "0", 1);
		i++;
	}
	return (padding);
}

int	print_nbr(int nbr, t_flags *f)
{
	long	nb;
	int		count;
	int		padding;
	int		nbrlen;
	char	sign;

	if (!f)
		return (nbr_recursive(nbr));
	count = 0;
	nbr_initializer(nbr, &nb, &nbrlen, f);
	sign = nbr_sign(nbr, f);
	padding = nbr_width(nbr, f);
	if (!f->hyphen && padding > 0 && (!f->zero || f->dot))
		count += nbr_padding(nbr, f);
	if (sign != '\0')
		count += ft_putchar(sign);
	if (!f->hyphen && padding > 0 && f->zero && !f->dot)
		count += nbr_zero_padding(nbr, f);
	if (f->dot && f->precision > nbr_count(nb))
		count += nbr_precision(nb, f);
	if (!(f->dot && f->precision == 0 && nbr == 0))
		count += nbr_recursive_digits(nb);
	if (f->hyphen && padding > 0)
		count += nbr_padding(nbr, f);
	return (count);
}
