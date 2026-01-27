/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:44:57 by juljin            #+#    #+#             */
/*   Updated: 2025/11/15 23:18:13 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strdup(char *s)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = malloc(gnl_strlen(s)+ 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strjoin(char *stash, char *buffer)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!stash)
		return (free(stash), gnl_strdup(buffer));
	joined = malloc(gnl_strlen(stash) + gnl_strlen(buffer) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		joined[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		joined[i + j] = buffer[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	i;

	slen = gnl_strlen(s);
	if (start >= slen)
		len = 0;
	else if (len > slen - start)
		len = slen - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*gnl_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
