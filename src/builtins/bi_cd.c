/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:41:26 by juljin            #+#    #+#             */
/*   Updated: 2026/02/06 19:42:48 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Save the oldpwd
void	env_oldpwd(t_env *env)
{
	t_env	*current;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			if (current->value)
				free(current->value);
			current->value = cwd;
			return ;
		}
		current = current->next;
	}
	free(cwd);
}

/* Search and retrieve the associated value of the given key in the env */
char	*env_get_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (key);
}

void	bi_cd(char *go_to, t_env *env)
{
	char	*home;
	char	*full_path;

	while (*go_to && ft_isspace(*go_to))
		go_to++;
	if (!*go_to)
		return ;
	if (ft_strncmp(go_to, "~", 1) == 0)
	{
		printf("%d\n", 0);
		home = env_get_value(env, "HOME");
		if (!home)
			return (free_env_list(env));
		full_path = ft_strjoin(home, go_to + 1);
		env_oldpwd(env);
		if (chdir(full_path) == -1)
		{
			print_error("minishell: cd: ", full_path,
				"No such file or directory");
			free(full_path);
			return ;
		}
		free(full_path);
	}
	if (ft_strncmp(go_to, "..", 2) == 0)
	{
		env_oldpwd(env);
		if (chdir(go_to) == -1)
			return ;
	}
}
/* 
int	main(int ac, char **av, char **env)
{
	t_env	*env_cpy;
	char	*path;
	t_env	*current;
	t_env	*env;
	char	*input;

	(void)ac;
	(void)av;
	env_cpy = copy_env(env);
	if (!env_cpy)
		return (1);
	current = env_cpy;
	path = "..";
	bi_cd(path, env_cpy);
	bi_cd(path, env_cpy);
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			printf("oldpwd: %s\n", current->value);
		}
		current = current->next;
	}
	bi_pwd();
	free_env_list(env_cpy);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*current;
	t_env	*env;
	
	(void)ac;
	(void)av;
	env = copy_env(envp);
	if (!env)
		return (1);
	current = env;
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (ft_strcmp(input, "cd") == 0)
		{
			bi_cd(input + 2, env);
			current = env;
			while (current)
			{
				if (ft_strcmp(current->key, "OLDPWD") == 0)
				{
					printf("oldpwd: %s\n", current->value);
				}
				current = current->next;
			}
		}
		if (ft_strcmp(input, "pwd") == 0)
			bi_pwd();
		if (ft_strcmp(input, "env") == 0)
			bi_env(env);
	}
	free_env_list(env);
	return (0);
}
 */