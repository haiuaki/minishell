/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:12:59 by juljin            #+#    #+#             */
/*   Updated: 2025/11/05 20:01:45 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static int	is_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*strim;
	size_t	beg;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	beg = 0;
	while (s1[beg] && is_set(s1[beg], set))
		beg++;
	end = ft_strlen(s1);
	while (end > beg && is_set(s1[end - 1], set))
		end--;
	strim = malloc(end - beg + 1);
	if (!strim)
		return (NULL);
	i = 0;
	while (i < end - beg)
	{
		strim[i] = s1[beg + i];
		i++;
	}
	strim[i] = '\0';
	return (strim);
}
