/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:09:38 by juljin            #+#    #+#             */
/*   Updated: 2026/02/01 16:36:09 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "includes.h"
# include "env.h"

/* -------------------------------- BUILTINS -------------------------------- */

void	bi_echo(char *str, int n_flag);
void	bi_env(t_env *head);
void	bi_exit(char *str);
void	bi_export(t_env *head);
void	bi_pwd(void);
void	bi_unset(char *str, t_env **head_ptr);

#endif