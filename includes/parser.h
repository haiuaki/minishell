/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:58:36 by juljin            #+#    #+#             */
/*   Updated: 2026/04/03 18:37:19 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

/* -------------------------------- COMMANDS -------------------------------- */

t_cmd	*get_cmd(t_token *token);
t_cmd	*create_cmd_struct(t_token *token);
void	cmd_add_back(t_cmd **head, t_cmd *new_cmd);
size_t	cmd_list_size(t_cmd *head);

/* ------------------------------ REDIRECTIONS ------------------------------ */

t_redir	*get_redir(t_token *token);
void	redir_add_back(t_redir **head, t_redir *new_redir);

/* --------------------------------- UTILS ---------------------------------- */

int		is_empty_unquoted(t_token *current);
char	**tokens_to_argv(t_token *token);

#endif
