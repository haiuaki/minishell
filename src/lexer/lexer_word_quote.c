/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:13:51 by juljin            #+#    #+#             */
/*   Updated: 2026/04/01 23:30:29 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Copies the characters one by one when outside of quotes.
 * Sets 'N' for "NONE" in the meta buffer because we are outside of quotes.
 * If a space or an operator is encountered, the current sequence
 * of characters for the token has been retrieved.
 * When encoutering `\`, it sets the meta char to 'E' for "Escaped".
 * It's useful for cases like : `echo \$USER`
 * The `\$` prevents the variable expansion.
 */
void	handle_no_quote(t_tokenizer *s)
{
	char	c;

	c = s->input[s->read_i];
	if (ft_isspace(c) || is_sep(c))
	{
		s->complete = 1;
		return ;
	}
	else if (is_quote(c))
		s->quote_char = c;
	else if (c == '\\' && s->input[s->read_i + 1])
	{
		s->buffer[s->write_i] = s->input[s->read_i + 1];
		s->meta_buffer[s->write_i] = 'E';
		s->write_i++;
		s->read_i++;
	}
	else
	{
		s->buffer[s->write_i] = c;
		s->meta_buffer[s->write_i] = 'N';
		s->write_i++;
	}
	s->read_i++;
}

/* 
 * Handles closing of quotes and manages `quote_meta_char` state
 * It also tracks quote boundaries to handle mixed quotes in a string.
 * e.g. :
 * Input : "$USER""$HOME""$SHELL""hello"
 * Meta : """""aaaaa""""""aaaaa
 */
static int	handle_quote_closure(t_tokenizer *s, char *quote_meta_char)
{
	if (s->input[s->read_i] != s->quote_char)
		return (0);
	s->quote_char = 0;
	if (s->input[s->read_i] == '"')
	{
		if (*quote_meta_char == '"')
			*quote_meta_char = 'a';
		else
			*quote_meta_char = '"';
	}
	return (1);
}

/* Handles escape sequences within double quotes */
static int	handle_escape_dquote(t_tokenizer *s)
{
	if (s->quote_char != '"' || s->input[s->read_i] != '\\')
		return (0);
	if (!s->input[s->read_i + 1])
		return (0);
	s->buffer[s->write_i] = s->input[s->read_i + 1];
	s->meta_buffer[s->write_i] = 'E';
	s->write_i++;
	s->read_i++;
	return (1);
}

/* Copies character and sets appropriate metadata based on quote type */
static void	copy_char_with_meta(t_tokenizer *s, char *quote_meta_char)
{
	s->buffer[s->write_i] = s->input[s->read_i];
	if (s->quote_char == '"')
		s->meta_buffer[s->write_i] = *quote_meta_char;
	else
		s->meta_buffer[s->write_i] = s->quote_char;
	s->write_i++;
}

/*
 * Copies characters one by one when inside of quotes.
 * Handles escape characters (e.g. echo hello Julien \& Sophie)
 * Sets a meta buffer for variable expansions.
 * If the meta buffer is something like : ''''' ('$USER')
 * The variable won't be expanded to its value, since it's literal.
 * Or, for double quotes : """"" ("$USER")
 * Here it will be expanded.
 * However : E"""" ("\$USER") won't be expanded because of the E.
 */
void	handle_in_quote(t_tokenizer *s, char *quote_meta_char)
{
	if (handle_quote_closure(s, quote_meta_char))
	{
		s->read_i++;
		return ;
	}
	if (handle_escape_dquote(s))
	{
		s->read_i++;
		return ;
	}
	copy_char_with_meta(s, quote_meta_char);
	s->read_i++;
}
