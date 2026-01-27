/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:28:51 by juljin            #+#    #+#             */
/*   Updated: 2026/01/03 22:18:25 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"

static void	leading_space_sign(const char *nptr, size_t *i, int *sign)
{
	while (nptr[*i] == ' ' || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static void	check_base(const char *nptr, size_t *i, int *base,
						unsigned long *limit)
{
	if (*base == 0)
	{
		if (nptr[*i] == '0' && (nptr[*i + 1] == 'x' || nptr[*i + 1] == 'X'))
			*base = 16;
		else if (nptr[*i] == '0')
			*base = 8;
		else
			*base = 10;
	}
	if (*base == 16 && nptr[*i] == '0' && (nptr[*i + 1] == 'x'
			|| nptr[*i + 1] == 'X'))
		*i += 2;
	*limit = ULONG_MAX / *base;
}

static void	set_digit(const char *nptr, int *digit, int i)
{
	if (nptr[i] >= '0' && nptr[i] <= '9')
		*digit = nptr[i] - '0';
	else if (nptr[i] >= 'a' && nptr[i] <= 'z')
		*digit = nptr[i] - 'a' + 10;
	else if (nptr[i] >= 'A' && nptr[i] <= 'Z')
		*digit = nptr[i] - 'A' + 10;
}

static void	set_result(unsigned long *result, unsigned long limit,
						int digit, int base)
{
	if (*result > limit || (*result == limit
			&& (unsigned long)digit > ULONG_MAX % base))
		*result = ULONG_MAX;
	else
		*result = *result * base + digit;
}

unsigned long	ft_strtoul(const char *nptr, char **endptr, int base)
{
	unsigned long	result;
	unsigned long	limit;
	int				digit;
	int				sign;
	size_t			i;

	i = 0;
	sign = 1;
	result = 0;
	leading_space_sign(nptr, &i, &sign);
	check_base(nptr, &i, &base, &limit);
	while (1)
	{
		digit = -1;
		set_digit(nptr, &digit, i);
		if (digit < 0 || digit >= base)
			break ;
		set_result(&result, limit, digit, base);
		i++;
	}
	if (endptr)
		*endptr = (char *)&nptr[i];
	return (result * sign);
}
