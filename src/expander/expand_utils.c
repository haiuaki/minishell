/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:49:53 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 20:50:20 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Concatenates two strings into a newly allocated string.
 * Frees the given string after the concatenation.
 */
char	*join_and_free(char *s1, char *s2)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	if (!joined_str)
		return (NULL);
	free(s1);
	free(s2);
	return (joined_str);
}

/* Retrieves the length of the key ($KEY; len = 3) */
size_t	get_keylen(char *key, char *meta)
{
	size_t	len;

	len = 0;
	if (key[len] == '?' || key[len] == '0')
		return (1);
	if (!ft_isalpha(key[len]) && key[len] != '_')
		return (0);
	len++;
	while (key[len] && (ft_isalnum(key[len]) || key[len] == '_')
		&& meta[len] == meta[0])
		len++;
	return (len);
}

/* 
 * Advances through the input while no literal ('$') or escaped (\$)
 * dollar sign ($) is encountered.
 * Once the pointer is on the dollar sign, creates a string of everything that
 * preceded it and joins it with the precedent stashed input.
 * If meta is provided, respects quoting. If NULL, treats all as unquoted.
 * Returns 0 if end of string, 1 otherwise.
 */
int	advance_until_var(t_expand *exp, size_t *i, size_t *j)
{
	*j = *i;
	if (exp->meta)
	{
		while (exp->val[*j] && (exp->val[*j] != '$' || exp->meta[*j] == '\''
				|| exp->meta[*j] == 'E'))
			(*j)++;
	}
	else
	{
		while (exp->val[*j] && exp->val[*j] != '$' && exp->val[*j] != '\\')
			(*j)++;
	}
	exp->sub = ft_substr(exp->val, *i, *j - *i);
	exp->new_val = join_and_free(exp->new_val, exp->sub);
	if (exp->val[*j] == '\0')
		return (0);
	return (1);
}

/*
 * Appends a single character from the original string to the new string.
 * Used for appending the `$` character when it's not a valid variable.
 */
void	join_one_char(t_expand *exp, size_t *j)
{
	exp->sub = ft_substr(exp->val, *j, 1);
	exp->new_val = join_and_free(exp->new_val, exp->sub);
}
