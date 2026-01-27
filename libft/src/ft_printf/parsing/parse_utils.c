/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 22:01:14 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:40 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialiser(t_flags *f)
{
	f->hyphen = 0;
	f->plus = 0;
	f->zero = 0;
	f->dot = 0;
	f->blank = 0;
	f->hash = 0;
	f->width = 0;
	f->precision = 0;
}

int	is_cspec(char c)
{
	char	*cspec;
	size_t	i;

	cspec = "cspdiuxX%";
	i = 0;
	while (cspec[i])
	{
		if (c == cspec[i])
			return (1);
		i++;
	}
	return (0);
}

void	get_width(const char **str, va_list *args, t_flags *f)
{
	int	wid;

	wid = va_arg(*args, int);
	if (wid < 0)
	{
		f->hyphen = 1;
		wid = -wid;
	}
	f->width = wid;
	(*str)++;
}

int	simple_atoi(const char **str)
{
	int	res;

	res = 0;
	while (is_digit(**str))
	{
		res = res * 10 + (**str - '0');
		(*str)++;
	}
	return (res);
}
