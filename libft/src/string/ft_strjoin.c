/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:12:37 by juljin            #+#    #+#             */
/*   Updated: 2025/11/05 20:00:38 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*sjoin;
	size_t	totlen;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	totlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	sjoin = malloc(totlen);
	if (!sjoin)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		sjoin[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		sjoin[i + j] = s2[j];
		j++;
	}
	sjoin[i + j] = '\0';
	return (sjoin);
}
