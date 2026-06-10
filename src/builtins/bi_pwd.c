/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:41:37 by juljin            #+#    #+#             */
/*   Updated: 2026/03/13 08:53:45 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `pwd` */
void	bi_pwd(t_shell *s, t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	s->last_exit_code = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_error("pwd: error retrieving current directory: ",
			"getcwd: cannot access parent directories", strerror(errno));
		s->last_exit_code = 1;
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
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
