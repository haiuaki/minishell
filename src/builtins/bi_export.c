/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:02:54 by juljin            #+#    #+#             */
/*   Updated: 2026/01/27 14:20:45 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Implementation of the built-in command `export` */
void	bi_export(char *str, t_env **head_ptr)
{
	t_env	*tmp;
	t_env	*node;

	tmp = *head_ptr;
	while (*str && ft_isspace(*str))
		str++;
	if (*str)
	{
		node = new_env_node(str);
		if (!node)
		{
			free_env_list(*head_ptr);
			return ;
		}
		env_add_back(head_ptr, node);
	}
	else
	{
		while (tmp)
		{
			printf("export %s%c\"%s\"\n", tmp->key, '=', tmp->value);
			tmp = tmp->next;
		}
	}
}
/* 
int	main(int ac, char *av[], char *envp[])
{
	t_env	*env_copy;
	char	*input;

	(void)ac;
	(void)av;
	env_copy = copy_env(envp);
	if (!env_copy)
		return (1);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (ft_strncmp(input, "export", 6) == 0)
			bi_export(input + 6, &env_copy);
		if (ft_strcmp(input, "env") == 0)
			bi_env(env_copy);
		if (ft_strncmp(input, "unset", 5) == 0)
			bi_unset(input + 5, &env_copy);
		free(input);
	}
	return (0);
}
 */