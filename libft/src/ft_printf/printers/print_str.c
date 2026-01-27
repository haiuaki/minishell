/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:56:08 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:15:00 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	str_precision(int slen, t_flags *f)
{
	if (f->precision < slen)
		return (f->precision);
	return (slen);
}

static int	str_width(int printlen, t_flags *f)
{
	if (f->width > 0)
		return (f->width - printlen);
	return (0);
}

static int	str_padding(int printlen, t_flags *f)
{
	int	padding;
	int	i;

	if (!f)
		return (0);
	padding = str_width(printlen, f);
	i = 0;
	while (i < padding)
	{
		write(1, " ", 1);
		i++;
	}
	return (padding);
}

int	print_str(char *s, t_flags *f)
{
	int	count;
	int	printlen;
	int	padding;

	if (!s)
		s = "(null)";
	if (!f)
		return (ft_putstr(s));
	if (f->dot)
		printlen = str_precision(ft_getlen(s), f);
	else
		printlen = ft_getlen(s);
	padding = str_width(printlen, f);
	count = 0;
	if (!f->hyphen && padding > 0)
		count += str_padding(printlen, f);
	if (printlen > 0)
		count += write(1, s, printlen);
	if (f->hyphen && padding > 0)
		count += str_padding(printlen, f);
	return (count);
}
