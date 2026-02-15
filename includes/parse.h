/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:34:22 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 15:40:18 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "includes.h"

/* ------------------------------- STRUCTURES ------------------------------- */

/* 
 * A token is a sequence of characters that represents specific elements in
 * the program, such as keyword, variable, operator or punctuation.
 */

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
}	t_token_type;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

typedef struct s_token
{
	char			*value;
	t_quote			q_type;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

/* --------------------------------- LEXER ---------------------------------- */

t_token	*tokenizer(char *input);
t_token	*create_token(char *str, size_t *i);

/* --------------------------------- UTILS ---------------------------------- */
int		is_quote(char c);
int		is_sep(char c);
void	token_add_back(t_token **head, t_token *new_node);
void	free_token_node(t_token *node);
void	free_token_list(t_token *head);

#endif
