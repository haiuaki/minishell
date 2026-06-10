/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:43:54 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 22:38:03 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Simpler version of get_keylen for heredoc - no meta buffer needed */
static size_t	get_keylen_heredoc(char *key)
{
	size_t	len;

	len = 0;
	if (key[len] == '?' || key[len] == '0')
		return (1);
	if (!ft_isalpha(key[len]) && key[len] != '_')
		return (0);
	len++;
	while (key[len] && (ft_isalnum(key[len]) || key[len] == '_'))
		len++;
	return (len);
}

/*
 * Handles special characters (\ and $) during heredoc expansion.
 * Specifically handles backslash escaping and variable expansion.
 */
static void	handle_heredoc_char(t_shell *s, t_expand *exp, size_t *i, size_t j)
{
	if (exp->val[j] == '\\')
	{
		if (exp->val[j + 1] == '$' || exp->val[j + 1] == '\\')
			j++;
		join_one_char(exp, &j);
		*i = j + 1;
	}
	else
	{
		*i = j + 1;
		exp->keylen = get_keylen_heredoc(&exp->val[*i]);
		if (exp->keylen > 0)
			expand_variable(s, exp, i);
		else
			join_one_char(exp, &j);
	}
}

/*
 * Expands variables in a heredoc string (content only).
 * Always expands all variables (no quoting context in heredoc content).
 * Used for expanding heredoc content when delimiter was unquoted.
 */
char	*expand_heredoc_string(t_shell *s, char *str)
{
	t_expand	exp;
	size_t		i;
	size_t		j;

	if (!str)
		return (NULL);
	exp.new_val = ft_strdup("");
	if (!exp.new_val)
		return (NULL);
	exp.val = str;
	exp.meta = NULL;
	i = 0;
	while (exp.val[i])
	{
		if (!advance_until_var(&exp, &i, &j))
			break ;
		handle_heredoc_char(s, &exp, &i, j);
	}
	return (exp.new_val);
}
