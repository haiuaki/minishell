/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:52:32 by juljin            #+#    #+#             */
/*   Updated: 2026/03/30 21:57:35 by juljin           ###   ########.fr       */
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

/* 
 * When no argument is given to the `exit` command,
 * retrieves the exit code of the last executed command
 * and exits with this value.
 */
static void	exit_no_arg(t_shell *s)
{
	long long	exit_code;

	exit_code = s->last_exit_code;
	free_shell_struct(s);
	exit(exit_code);
}

/* Implementation of the built-in command `exit` */
void	bi_exit(t_shell *s, t_cmd *cmd)
{
	long long	exit_code;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->args[1])
		exit_no_arg(s);
	if (!is_num(cmd->args[1]))
	{
		print_error("minishell: exit: ", cmd->args[1],
			"numeric argument required");
		free_shell_struct(s);
		exit(2);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		s->last_exit_code = 1;
		return ;
	}
	exit_code = ft_atol(cmd->args[1]);
	free_shell_struct(s);
	exit(exit_code);
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
