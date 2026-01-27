/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:12:20 by juljin            #+#    #+#             */
/*   Updated: 2025/12/04 14:38:07 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static char	*split_dup(const char *s, char c)
{
	char	*dup;
	size_t	slen;
	size_t	i;

	slen = 0;
	i = 0;
	while (s[slen] && s[slen] != c)
		slen++;
	dup = malloc(slen + 1);
	if (!dup)
		return (NULL);
	while (i < slen)
	{
		dup[i] = s[i];
		i++;
	}
	dup[slen] = '\0';
	return (dup);
}

static size_t	word_count(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**free_arr(char **arr, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;

	arr = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			arr[j] = split_dup(&s[i], c);
			if (!arr[j])
				return (free_arr(arr, j));
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	arr[j] = NULL;
	return (arr);
}
// could add at the beginning of ft_split :

// if (!s)
// 	return (NULL);

// if we want to make it NULL-proof but it goes over 25 lines.
// OR we can remove the free() loop
// but that also takes 2 lines and 1 helper function
