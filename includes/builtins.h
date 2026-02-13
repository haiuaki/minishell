/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:09:38 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 18:55:33 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "includes.h"
# include "env.h"
# include "parse.h"

/* -------------------------------- MACROS ---------------------------------- */

# define ORPHANED_DIR "getcwd: cannot access parent directories: \
No such file or directory"

/* -------------------------------- BUILTINS -------------------------------- */

void	bi_cd(t_token *token, t_env *env);
void	bi_echo(t_token *token, int n_flag);
void	bi_env(t_env *head);
void	bi_exit(t_token *token);
void	bi_export(t_token *token, t_env **head_ptr);
void	bi_pwd(t_env *env);
void	bi_unset(t_token *token, t_env **head_ptr);

#endif