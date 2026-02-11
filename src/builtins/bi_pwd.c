/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:41:37 by juljin            #+#    #+#             */
/*   Updated: 2026/02/11 18:22:13 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `pwd` */

void	bi_pwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (errno == ENOENT)
			return (env->is_orphaned = 1, free(cwd), print_error("pwd: ",
					"error retrieving current directory", ORPHANED_DIR));
		else
			return (env->is_orphaned = 1, free(cwd), print_error("minishell: ",
					"getcwd", strerror(errno)));
	}
	printf("%s\n", cwd);
	free(cwd);
}
/*
int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (ft_strcmp(input, "pwd") == 0)
			bi_pwd();
	}
	return (0);
}
*/