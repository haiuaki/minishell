/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:56:23 by juljin            #+#    #+#             */
/*   Updated: 2026/02/13 10:15:50 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Scans and tokenizes the user's input */
t_token	*tokenizer(char *input)
{
	t_token	*head;
	t_token	*token;
	size_t	i;

	i = 0;
	head = NULL;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		token = create_token(input, &i);
		if (!token)
			return (free_token_list(head), NULL);
		token_add_back(&head, token);
	}
	return (head);
}
/*
int	main(void)
{
	t_token	*tokens;
	t_token	*tmp;
	char	*input;

	while (1)
	{
		tokens = NULL;
		input = readline(PROMPT);
		if (!input)
			return (free_token_list(tokens), 1);
		if (input && *input)
		{
			add_history(input);
			tokens = tokenizer(input);
			if (!tokens)
				return (free(input), 1);
		}
		tmp = tokens;
		while (tmp)
		{
			printf("[%u] %s\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		free_token_list(tokens);
		free(input);
	}
	return (0);
}
*/
