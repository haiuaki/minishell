/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:48:20 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 18:23:32 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	token_size(t_token *token)
{
	t_token	*current;
	size_t	i;

	i = 0;
	if (!token)
		return (0);
	current = token;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/* Converting the token_list to an array of strings */
char	**token_to_array(t_token *token)
{
	t_token	*current;
	size_t	i;
	char	**res;

	if (!token)
		return (NULL);
	res = malloc(sizeof(char *) * (token_size(token) + 1));
	if (!res)
		return (NULL);
	i = 0;
	current = token;
	while (current)
	{
		res[i] = ft_strdup(current->value);
		if (!res[i])
			return (ft_free_array(res), NULL);
		i++;
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}

/* Implementation of the built-in command `echo` with `-n` option */
void	bi_echo(t_token *token, int n_flag)
{
	char	**args;
	size_t	i;

	args = token_to_array(token);
	if (!args)
		return (ft_putchar_fd('\n', 1));
	i = 1;
	if (n_flag)
		i = 2;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}

/* void	bi_echo(char *str, int n_flag)
{
	char	*input;
	char	*arg;

	if (*str)
		printf("%s", str);
	if (!n_flag)
		printf("\n");
} */
/*
int	main(void)
{
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
