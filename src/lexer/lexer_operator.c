/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:53:08 by juljin            #+#    #+#             */
/*   Updated: 2026/04/02 12:34:09 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Creates a token when the pointed character is an operator.
 * If so, creates an individual token for it.
 * Handles `>>` and `<<` by checking the following character.
 */
t_token	*tokenize_operator(const char *str, size_t *i)
{
	t_token	*new_token;
	size_t	len;

	len = 1;
	if ((str[*i] == '|' || str[*i] == '&' || str[*i] == '>' || str[*i] == '<')
		&& str[*i + 1] == str[*i])
	{
		if (str[*i] == '<' && str[*i + 2] == str[*i])
			len = 3;
		else
			len = 2;
	}
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_substr(str, *i, len);
	new_token->meta = ft_strdup("");
	if (!new_token->value || !new_token->meta)
		return (free_token_node(new_token), NULL);
	set_token_type(new_token);
	*i += len;
	return (new_token);
}
