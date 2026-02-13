/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:52:32 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 18:42:46 by sopelet          ###   ########.fr       */
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
void	bi_exit(t_token *token)
{
	int		status;

	write(2, "exit\n", 5);
	if (!token->next)
		exit(EXIT_SUCCESS);
	token = token->next;
	if (is_num(token->value))
		status = ft_atoi(token->value);
	else
	{
		print_error("minishell: exit: ", token->value,
			"numeric argument required.");
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
