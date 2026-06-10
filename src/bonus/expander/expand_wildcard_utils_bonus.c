/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:58:31 by juljin            #+#    #+#             */
/*   Updated: 2026/04/13 16:58:08 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Pattern matching function. Returns 1 if filename matches pattern. */
int	wildcard_match(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (1);
	if (*pattern == '*')
	{
		if (wildcard_match(pattern + 1, filename))
			return (1);
		if (*filename != '\0' && wildcard_match(pattern, filename + 1))
			return (1);
		return (0);
	}
	if (*pattern == *filename)
		return (wildcard_match(pattern + 1, filename + 1));
	return (0);
}

/* Sort an array of strings alphabetically */
void	sort_matches(char **matches, size_t count)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(matches[i], matches[j]) > 0)
			{
				tmp = matches[i];
				matches[i] = matches[j];
				matches[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Helper function to clean the array of strings of filenames */
void	free_matches_array(char **matches, size_t count)
{
	size_t	i;

	if (!matches)
		return ;
	i = 0;
	while (i < count)
	{
		free(matches[i]);
		i++;
	}
	free(matches);
}

/* Create a new token node with the given value */
t_token	*create_match_token(char *value, t_token *original)
{
	t_token	*new;
	size_t	len;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), NULL);
	len = ft_strlen(value);
	new->meta = ft_calloc(len + 1, sizeof(char));
	if (!new->meta)
		return (free(new->value), free(new), NULL);
	ft_memset(new->meta, 'N', len);
	new->type = original->type;
	return (new);
}

/* Helper to handle directory traversal and filtering entries. */
char	**collect_matching_names(char *pattern, size_t *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;

	matches = ft_calloc(128, sizeof(char *));
	dir = opendir(".");
	if (!matches || !dir)
		return (free(matches), NULL);
	*count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == '.' && pattern[0] != '.')
			&& wildcard_match(pattern, entry->d_name))
		{
			matches[(*count)++] = ft_strdup(entry->d_name);
			if (!matches[*count - 1])
				return (free_matches_array(matches, *count - 1),
					closedir(dir), NULL);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}
