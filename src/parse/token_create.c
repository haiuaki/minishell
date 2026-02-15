/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:43:10 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 16:01:28 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to set the token type of each token */
static void	set_token_type(t_token *token)
{
	if (ft_strcmp(token->value, "|") == 0)
		token->type = TK_PIPE;
	else if (ft_strcmp(token->value, ">") == 0)
		token->type = TK_REDIR_OUT;
	else if (ft_strcmp(token->value, "<") == 0)
		token->type = TK_REDIR_IN;
	else if (ft_strcmp(token->value, ">>") == 0)
		token->type = TK_APPEND;
	else if (ft_strcmp(token->value, "<<") == 0)
		token->type = TK_HEREDOC;
	else
		token->type = TK_WORD;
}
/*
 * Helper function to determine the token's length.
 * If the token is in quotes, will enter a 'in_quote' mode
 * and will retrieve the entire "word" inside the quotes.
 * (e.g. echo "ls | grep" ; "ls | grep" will be the value
 * of the token and will be a `TK_WORD` type)
 */
static size_t	set_word_len(char *str, size_t *i)
{
	size_t	len;
	char	c;
	char	in_quote;

	len = 0;
	while (str[*i + len])
	{
		c = str[*i + len];
		if (is_quote(c))
		{
			if (in_quote == 0)
				in_quote = c;
			else if (in_quote == c)
				in_quote = 0;
		}
		if (!in_quote && (ft_isspace(c) || is_sep(c)))
			break ;
		len++;
	}
	return (len);
}

static t_token	*tokenize_operator(char *str, size_t *i)
{
	t_token	*new_token;
	size_t	len;

	len = 1;
	if (str[*i] != '|' && str[*i + 1] == str[*i])
		len = 2;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_substr(str, *i, len);
	if (!new_token->value)
		return (free_token_node(new_token), NULL);
	set_token_type(new_token);
	*i += len;
	return (new_token);
}

/*
 * Helper function to create a token of a word, if the word is in quotes
 * strips the quotes and keep the word only.
 */
static t_token	*tokenize_word(char *str, size_t *i)
{
	t_token	*new_token;
	size_t	len;

	len = set_word_len(str, i);
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (len > 1 && is_quote(str[*i]) && str[*i] == str[*i + len - 1])
		new_token->value = ft_substr(str, *i + 1, len - 2);
	else
		new_token->value = ft_substr(str, *i, len);
	if (!new_token->value)
		return (free_token_node(new_token), NULL);
	set_token_type(new_token);
	*i += len;
	return (new_token);
}

/*
 * Helper function to create a token
 * If the first character pointed by str is an operator,
 * it creates a token for it.
 */
t_token	*create_token(char *str, size_t *i)
{
	if (is_sep(str[*i]))
		return (tokenize_operator(str, i));
	else
		return (tokenize_word(str, i));
}
