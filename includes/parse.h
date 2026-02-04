/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:34:22 by juljin            #+#    #+#             */
/*   Updated: 2026/02/02 17:18:38 by juljin           ###   ########.fr       */
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

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	struct s_token_type		*next;
}							t_token;

#endif