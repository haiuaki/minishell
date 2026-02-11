/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:09:38 by juljin            #+#    #+#             */
/*   Updated: 2026/02/11 18:11:20 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "includes.h"
# include "env.h"

/* -------------------------------- MACROS ---------------------------------- */

# define ORPHANED_DIR "getcwd: cannot access parent directories: \
No such file or directory"

/* -------------------------------- BUILTINS -------------------------------- */

void	bi_cd(char *go_to, t_env *env);
void	bi_echo(char *str, int n_flag);
void	bi_env(t_env *head);
void	bi_exit(char *str);
void	bi_export(char *str, t_env **head_ptr);
void	bi_pwd(t_env *env);
void	bi_unset(char *key_str, t_env **head_ptr);

#endif