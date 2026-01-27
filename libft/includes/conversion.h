/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:15:44 by juljin            #+#    #+#             */
/*   Updated: 2026/01/03 22:17:53 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSION_H
# define CONVERSION_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>

int				ft_atoi(const char *str);
long			ft_atol(const char *str);
char			*ft_itoa(int n);
unsigned long	ft_strtoul(const char *nptr, char **endptr, int base);

#endif