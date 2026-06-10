/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:44:27 by juljin            #+#    #+#             */
/*   Updated: 2026/04/07 02:42:38 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# include "includes.h"

/* --------------------------------- MACROS --------------------------------- */

# define ERROR_OPERATOR "minishell: syntax error near unexpected token "

/* ----------------------------- ERROR PRINTERS ----------------------------- */

void	print_error(const char *prefix, const char *name, const char *msg);
void	print_key_error(char *cmd, char *arg);
void	print_error_op(const char *msg, const char *name);

/* ----------------------------- SYNTAX ERRORS ------------------------------ */

int		handle_op_error(t_shell *s, t_token *token);
int		handle_link(t_token *tokens);

/* ----------------------------- SYNTAX CHECKS ------------------------------ */

int		check_operator_syntax(t_shell *s, t_token *token);
int		check_link_syntax(t_shell *s, t_token *token);
int		check_paren_syntax(t_shell *s, t_token *token);
int		check_paren_balance(t_shell *s, t_token *tokens);

#endif
