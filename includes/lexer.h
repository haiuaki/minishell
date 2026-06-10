/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:34:22 by juljin            #+#    #+#             */
/*   Updated: 2026/06/10 16:53:00 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

/* --------------------------------- LEXER ---------------------------------- */

t_token	*tokenizer(const char *input);
t_token	*tokenize_operator(const char *str, size_t *i);
t_token	*tokenize_word(const char *str, size_t *i);

/* ----------------------------- QUOTE HANDLING ----------------------------- */

void	handle_no_quote(t_tokenizer *s);
void	handle_in_quote(t_tokenizer *s, char *quote_meta_char);

/* --------------------------------- UTILS ---------------------------------- */

void	print_quote_error(char c);

int		is_quote(char c);
int		is_sep(char c);
int		is_operator(t_token *token);
int		is_link(t_token *token);
int		is_incomplete_mandatory(t_token *tokens);
void	set_token_type(t_token *token);

static inline int	is_incomplete(t_token *tokens)
{
	return (is_incomplete_mandatory(tokens));
}

/* ------------------------------- LIST UTILS ------------------------------- */

void	token_add_back(t_token **head, t_token *new_node);
t_token	*token_get_last(t_token *node);
size_t	token_list_size(t_token *head);

/* -------------------------------- CLEANUP --------------------------------- */

void	free_token_node(t_token *node);
void	free_token_list(t_token *head);

#endif
