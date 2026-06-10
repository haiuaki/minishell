/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:09:38 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 13:51:45 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

/* -------------------------------- BUILTINS -------------------------------- */

void	bi_cd(t_shell *s, t_cmd *cmd);
void	bi_echo(t_shell *s, t_cmd *cmd);
void	bi_env(t_shell *s, t_cmd *cmd);
void	bi_exit(t_shell *s, t_cmd *cmd);
void	bi_export(t_shell *s, t_cmd *cmd);
void	bi_pwd(t_shell *s, t_cmd *cmd);
void	bi_unset(t_shell *s, t_cmd *cmd);

/* --------------------------------- UTILS ---------------------------------- */

void	print_key_error(char *cmd, char *arg);
int		key_isalnum(char *key);

void	handle_chdir_error(t_shell *s, char *target,
			char *old_pwd_save, char *parent_path);
t_env	*get_sorted_env(t_env *original_list);

#endif
