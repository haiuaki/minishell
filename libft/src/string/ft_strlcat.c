/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:12:40 by juljin            #+#    #+#             */
/*   Updated: 2025/11/05 20:47:34 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = 0;
	slen = ft_strlen(src);
	while (dlen < dstsize && dst[dlen])
		dlen++;
	if (dlen >= dstsize)
		return (dstsize + slen);
	i = 0;
	while (src[i] && (dlen + i + 1) < dstsize)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	if (dlen + i < dstsize)
		dst[dlen + i] = '\0';
	return (dlen + slen);
}

// for the first while() loop : until it finds a \0 or reaches dsize
// "strlcat() takes the full size of the destination buffer and
// guarantee NUL-termination if there is room."
// "Note that room for the NUL should be included in dstsize."
// Hence the following so it doesn't keep scanning looking for \0
// (reason why not using ft_strlen)
