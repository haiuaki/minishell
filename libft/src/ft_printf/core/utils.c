/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:39:54 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:15:08 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_getlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
	return (len);
}
