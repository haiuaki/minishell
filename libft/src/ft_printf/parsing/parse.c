/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:45:43 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:38 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_precision(const char **str, va_list *args, t_flags *f)
{
	f->dot = 1;
	if (**str == '*')
	{
		f->precision = va_arg(*args, int);
		(*str)++;
	}
	else
		f->precision = simple_atoi(str);
}

static int	parse_simple(const char **str, t_flags *f)
{
	if (**str == '-')
		f->hyphen = 1;
	else if (**str == '+')
		f->plus = 1;
	else if (**str == '0' && f->width == 0 && f->dot == 0)
		f->zero = 1;
	else if (**str == ' ')
		f->blank = 1;
	else if (**str == '#')
		f->hash = 1;
	else
		return (0);
	(*str)++;
	return (1);
}

static int	parse_difficult(const char **str, va_list *args, t_flags *f)
{
	if (**str == '.')
	{
		(*str)++;
		parse_precision(str, args, f);
		return (1);
	}
	else if (**str == '*')
	{
		get_width(str, args, f);
		return (1);
	}
	else if (is_digit(**str))
	{
		f->width = simple_atoi(str);
		return (1);
	}
	return (0);
}

// f->hyphen = 1 because if width < 0, align to the left. works as a '-'
// 0 would be ignored.

void	parse_flags(const char **str, va_list *args, t_flags *f)
{
	while (**str && !is_cspec(**str))
	{
		if (!parse_simple(str, f))
		{
			if (!parse_difficult(str, args, f))
				(*str)++;
		}
	}
}
