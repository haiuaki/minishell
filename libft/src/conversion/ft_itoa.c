/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:11:47 by juljin            #+#    #+#             */
/*   Updated: 2025/11/11 17:09:14 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"

static size_t	count_digits(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nb;
	size_t	size;

	nb = n;
	size = count_digits(nb);
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	result[size] = '\0';
	if (nb == 0)
		result[0] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		result[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (result);
}
