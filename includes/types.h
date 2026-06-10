/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 12:00:00 by jlnjin            #+#    #+#             */
/*   Updated: 2026/06/09 12:00:00 by jlnjin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/* ----------------------------- LEXER ENUMS ------------------------------- */

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_OR,
	TK_AND,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_HERESTRING,
	TK_LPAREN,
	TK_RPAREN
}	t_token_type;

/* ----------------------- CORE FORWARD DECLARATIONS ------------------------ */

typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_tokenizer	t_tokenizer;
typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
typedef struct s_pipe		t_pipe;
typedef struct s_shell		t_shell;

#endif
