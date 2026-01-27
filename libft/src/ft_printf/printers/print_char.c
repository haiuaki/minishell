/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:54:51 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:43 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	char_width(t_flags *f)
{
	if (f->width > 1)
		return (f->width - 1);
	return (0);
}

static int	char_padding(t_flags *f)
{
	int	padding;
	int	i;

	if (!f)
		return (0);
	padding = char_width(f);
	i = 0;
	while (i < padding)
	{
		write(1, " ", 1);
		i++;
	}
	return (padding);
}

int	print_char(char c, t_flags *f)
{
	int	count;

	if (!f)
		return (write(1, &c, 1));
	count = 0;
	if (!f->hyphen)
		count += char_padding(f);
	write(1, &c, 1);
	count++;
	if (f->hyphen)
		count += char_padding(f);
	return (count);
}
