/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:48:20 by juljin            #+#    #+#             */
/*   Updated: 2026/02/01 16:04:58 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `echo` with `-n` option */
void	bi_echo(char *str, int n_flag)
{
	if (*str)
		printf("%s", str);
	if (!n_flag)
		printf("\n");
}
/*
int	main(void)
{
	char	*input;
	char	*arg;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (ft_strncmp(input, "echo -n", 7) == 0)
		{
			arg = input + 7;
			while (*arg && ft_isspace(*arg))
				arg++;
			bi_echo(arg, 1);
		}
		else if (ft_strncmp(input, "echo", 4) == 0)
		{
			arg = input + 4;
			while (*arg && ft_isspace(*arg))
				arg++;
			bi_echo(arg, 0);
		}
	}
	return (0);
}
*/
