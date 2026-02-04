/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:52:32 by juljin            #+#    #+#             */
/*   Updated: 2026/02/01 16:03:28 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to check if the given argument to `exit` is numeric */
static int	is_num(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Implementation of the built-in command `exit` */
void	bi_exit(char *str)
{
	int		status;
	char	*arg;
	char	*end;

	write(2, "exit\n", 5);
	arg = str + 4;
	while (*arg && ft_isspace(*arg))
		arg++;
	if (!*arg)
		exit(EXIT_SUCCESS);
	end = arg;
	while (*end && !ft_isspace(*end))
		end++;
	*end = '\0';
	if (is_num(arg))
		status = ft_atoi(arg);
	else
	{
		print_error("minishell: exit: ", arg, "numeric argument required.");
		status = 2;
	}
	exit(status);
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
		if (ft_strcmp(input, "exit") == 0)
			bi_exit(input);
	}
	return (0);
}
*/
