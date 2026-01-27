/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:12:03 by juljin            #+#    #+#             */
/*   Updated: 2025/11/05 16:51:23 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
// (unsigned char)c because a char is always 1 byte, and int is 4 bytes
// we cast b as (unsigned char *) because void* cannot be indexed
// and we also cannot dereference it
// and void* can point to any type of memory char[], int[], struct, etc...
