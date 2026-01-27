/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:54:52 by juljin            #+#    #+#             */
/*   Updated: 2025/11/25 16:14:58 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	nbr_initializer(int nbr, long *nb, int *nbrlen, t_flags *f)
{
	*nb = nbr_abs(nbr);
	*nbrlen = nbr_count(*nb);
	if (f->dot && f->precision > *nbrlen)
		*nbrlen = f->precision;
}
