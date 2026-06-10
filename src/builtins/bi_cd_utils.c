/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:53:53 by juljin            #+#    #+#             */
/*   Updated: 2026/03/23 12:26:15 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Checks the current directory to see if it's a permission error,
 * handles the error like bash, however it may be more relevant to
 * leave strerror() handle the correct error messages for a more
 * compliant shell.
 * Frees the allocated memory and set the exit code to `1`.
 */
void	handle_chdir_error(t_shell *s, char *target,
				char *old_pwd_save, char *parent_path)
{
	if (parent_path)
		free(parent_path);
	if (errno == EACCES && access(".", R_OK | X_OK) == -1)
		print_error("minishell: cd: ", target, "Not a directory");
	else
		print_error("minishell: cd: ", target, strerror(errno));
	if (old_pwd_save)
		free(old_pwd_save);
	s->last_exit_code = 1;
}
