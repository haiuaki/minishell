/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:43:10 by juljin            #+#    #+#             */
/*   Updated: 2026/04/01 23:16:25 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes the `t_tokenizer` struct */
static int	init_tokenizer_struct(const char *str, size_t *i, t_tokenizer *s)
{
	size_t	len;

	ft_bzero(s, sizeof(t_tokenizer));
	s->input = str + *i;
	len = ft_strlen(s->input);
	s->buffer = ft_calloc(len + 1, sizeof(char));
	if (!s->buffer)
		return (0);
	s->meta_buffer = ft_calloc(len + 1, sizeof(char));
	if (!s->meta_buffer)
		return (free(s->buffer), 0);
	return (1);
}

/* Creates the new token and retrieves the buffer and meta buffer */
static t_token	*finalize_token(t_tokenizer *state, size_t *i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		free(state->buffer);
		free(state->meta_buffer);
		return (NULL);
	}
	new_token->value = ft_strdup(state->buffer);
	new_token->meta = ft_strdup(state->meta_buffer);
	free(state->buffer);
	free(state->meta_buffer);
	if (!new_token->value || !new_token->meta)
		return (free_token_node(new_token), NULL);
	set_token_type(new_token);
	*i += state->read_i;
	return (new_token);
}

/*
 * Create a token of a word, if the word is in quotes,
 * strips the quotes and keeps the word only.
 * Handles escape characters and variable expansion with a meta buffer.
 * If the token hasn't been properly ended by a quote (if it started with one)
 * it returns 'NULL' and free everything.
 */
t_token	*tokenize_word(const char *str, size_t *i)
{
	t_tokenizer	state;
	char		quote_meta_char;

	quote_meta_char = '"';
	if (!init_tokenizer_struct(str, i, &state))
		return (NULL);
	while (state.input[state.read_i])
	{
		if (state.quote_char)
			handle_in_quote(&state, &quote_meta_char);
		else
			handle_no_quote(&state);
		if (state.complete)
			break ;
	}
	if (state.quote_char != 0)
	{
		print_quote_error(state.quote_char);
		free(state.buffer);
		free(state.meta_buffer);
		return (NULL);
	}
	return (finalize_token(&state, i));
}
