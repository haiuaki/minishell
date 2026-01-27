/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:45:07 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 17:07:12 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_hash(char c)
{
	int	count;

	count = 0;
	if (c == 'X')
		count += ft_putstr("0X");
	else
		count += ft_putstr("0x");
	return (count);
}

static int	hex_precision(unsigned long nbr, t_flags *f)
{
	int	precision;
	int	i;

	precision = f->precision - hex_count(nbr);
	i = 0;
	while (i < precision)
	{
		write(1, "0", 1);
		i++;
	}
	return (precision);
}

// if nb of digits < precision, padd with zeros on the left.

static int	hex_recursive(unsigned long nbr, char c)
{
	char	*base;
	int		count;

	count = 0;
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nbr >= 16)
		count += hex_recursive(nbr / 16, c);
	count += ft_putchar(base[nbr % 16]);
	return (count);
}

int	print_hex(unsigned long nbr, char c, t_flags *f)
{
	int	hexlen;
	int	hexprefix;
	int	padding;
	int	count;

	if (!f)
		return (hex_recursive(nbr, c));
	count = 0;
	hex_init(nbr, f, &hexlen, &hexprefix);
	if (c == 'p')
		hexprefix = 2;
	padding = hex_width(hexlen, hexprefix, f);
	if (!f->hyphen && padding > 0 && (!f->zero || f->dot))
		count += hex_padding(hexlen, hexprefix, f);
	if ((f->hash && nbr != 0) || c == 'p')
		count += hex_hash(c);
	if (!f->hyphen && padding > 0 && f->zero && !f->dot)
		count += hex_zero_padding(hexlen, hexprefix, f);
	if (f->dot && f->precision > hex_count(nbr))
		count += hex_precision(nbr, f);
	if (!(f->dot && f->precision == 0 && nbr == 0))
		count += hex_recursive(nbr, c);
	if (f->hyphen && padding > 0)
		count += hex_padding(hexlen, hexprefix, f);
	return (count);
}
