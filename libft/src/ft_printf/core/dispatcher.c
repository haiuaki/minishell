/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:01:25 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:39:53 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dispatcher(char c, va_list *args, int *count, t_flags *f)
{
	void	*ptr;

	if (c == 'c')
		*count += print_char((char)va_arg(*args, int), f);
	else if (c == 's')
		*count += print_str(va_arg(*args, char *), f);
	else if (c == 'p')
	{
		ptr = va_arg(*args, void *);
		if (!ptr)
			*count += print_str("(nil)", f);
		else
			*count += print_hex((unsigned long)ptr, c, f);
	}
	else if (c == 'd' || c == 'i')
		*count += print_nbr(va_arg(*args, int), f);
	else if (c == 'u')
		*count += print_unsign(va_arg(*args, unsigned int), f);
	else if (c == 'x' || c == 'X')
		*count += print_hex((unsigned long)va_arg(*args, unsigned int), c, f);
	else if (c == '%')
		*count += ft_putchar('%');
}
