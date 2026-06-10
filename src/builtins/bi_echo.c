/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:48:20 by juljin            #+#    #+#             */
/*   Updated: 2026/04/13 14:35:54 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Helper function to check if the given option is `-n`.
 * It also helps to handle cases such as `echo -nnnn` or `echo -n -n -n`.
 * Returns 1 if it's only `n`, 0 otherwise.
 */
static int	is_all_n(char *str)
{
	size_t	i;

	if (!str || str[0] != '-' || str[1] == '\0')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/* Implementation of the built-in command `echo` with `-n` option */
void	bi_echo(t_shell *s, t_cmd *cmd)
{
	size_t	i;
	int		n_flag;

	s->last_exit_code = 0;
	i = 1;
	n_flag = 0;
	while (cmd->args[i] && cmd->args[i][0] == '-' && is_all_n(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

/* void	bi_echo(t_shell *s, t_token *tk_curr, int n_flag)
{
	size_t	count;
	size_t	i;

	i = 0;
	s->last_exit_code = 0;
	if (n_flag)
		tk_curr = tk_curr->next->next;
	else
		tk_curr = tk_curr->next;
	count = token_list_size(tk_curr);
	while (tk_curr && i < count)
	{
		if (is_operator(tk_curr))
			break ;
		ft_putstr_fd(tk_curr->value, STDOUT_FILENO);
		if (tk_curr->next && !is_operator(tk_curr->next))
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
		tk_curr = tk_curr->next;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
} */
/*
int	main(void)
{
	t_token	*tokens;
	char	*input;

	while (1)
	{
		tokens = NULL;
		input = readline(PROMPT);
		if (!input)
			break ;
		if (input && *input)
		{
			add_history(input);
			tokens = tokenizer(input);
			if (!tokens)
				return (free(input), 1);
			if (!handle_op_error(tokens))
			{
				free(input);
				free_token_list(tokens);
				continue ;
			}
		}
		if (ft_strcmp(tokens->value, "echo") == 0)
		{
			if (tokens->next && ft_strcmp(tokens->next->value, "-n") == 0)
				bi_echo(tokens, 1);
			else
				bi_echo(tokens, 0);
		}
		free(input);
		free_token_list(tokens);
	}
	return (0);
}
*/
