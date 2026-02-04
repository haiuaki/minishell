/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:41:37 by juljin            #+#    #+#             */
/*   Updated: 2026/02/01 16:41:43 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `pwd` */
void	bi_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		print_error("minishell: ", "getcwd", strerror(errno));
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