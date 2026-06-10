/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:56:23 by juljin            #+#    #+#             */
/*   Updated: 2026/03/06 11:16:31 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Helper function to print the error message whenever a token's quote hasn't 
 * been closed. (this can be reproduced with 'ctrl+D' when typing `echo "...`
 * in bash.
 */
void	print_quote_error(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\'", 2);
	print_error("minishell: syntax error", "", "unexpected end of file");
}

/* Creates a token */
static t_token	*create_token(const char *str, size_t *i)
{
	if (is_sep(str[*i]))
		return (tokenize_operator(str, i));
	else
		return (tokenize_word(str, i));
}

/* Scans and tokenizes the user's input */
t_token	*tokenizer(const char *input)
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
			printf("[meta] %s\n", tmp->meta);
			printf("[addr] %p\n", tmp->value);
			tmp = tmp->next;
		}
		free_token_list(tokens);
		free(input);
	}
	return (0);
}*/
