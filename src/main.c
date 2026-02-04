/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:58:50 by juljin            #+#    #+#             */
/*   Updated: 2026/01/26 17:54:23 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char *av[])
{
	char	*input;

	(void)av;
	if (ac != 1)
		return (printf(USAGE), 1);
	while (1)
	{
		sig_set_parent();
		input = readline(PROMPT);
		if (!input)
			break ;
		if (input && *input)
			add_history(input);
		free(input);
	}
	return (0);
}
