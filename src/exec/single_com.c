/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_com.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:57:58 by sopelet           #+#    #+#             */
/*   Updated: 2026/02/13 19:37:28 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_token *token, t_env *env)
{
	t_token	*current;

	if (!token)
		return ;
	current = token;
	if (ft_strcmp(current->value, "cd") == 0 && current->next->type == TK_WORD)
		bi_cd(current, env);
	else if (ft_strcmp(current->value, "pwd") == 0)
		bi_pwd(env);
	else if (ft_strcmp(current->value, "echo") == 0)
	{
		if (current->next == NULL)
			return (bi_echo(NULL, 0));
		if (ft_strcmp(current->next->value, "-n") == 0)
			bi_echo(current, 1);
		else if (current->next->type == TK_WORD)
			bi_echo(current, 0);
	}
	else if (ft_strcmp(current->value, "env") == 0)
		bi_env(env);
	else if (ft_strcmp(current->value, "exit") == 0)
		bi_exit(current);
	else if (ft_strcmp(current->value, "export") == 0)
		bi_export(token, &env);
	else if (ft_strcmp(current->value, "unset") == 0)
		bi_unset(current, &env);
}
/* 
int	main(int ac, char **av, char **envp)
{
	t_env	*current;
	t_env	*env;
	t_token	*tokens;
	char	*input;

	(void)ac;
	(void)av;
	env = copy_env(envp);
	if (!env)
		return (1);
	current = env;
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
		exec_builtins(tokens, current);
		free_token_list(tokens);
		free(input);
	}
	return (0);
}
 */