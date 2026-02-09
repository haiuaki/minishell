/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:41:26 by juljin            #+#    #+#             */
/*   Updated: 2026/02/09 20:12:06 by sopelet          ###   ########.fr       */
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

// Update the current pwd
void	env_current_pwd(t_env *env)
{
	t_env	*current;
	char	*cur_path;

	cur_path = getcwd(NULL, 0);
	if (!cur_path)
		return ;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			if (current->value)
				free(current->value);
			current->value = cur_path;
			return ;
		}
		current = current->next;
	}
	free(cur_path);
}

// Handle "cd ~"
static void	handle_tilde(char *go_to, t_env *env)
{
	char	*home;
	char	*full_path;

	home = env_get_value(env, "HOME");
	if (!home)
		return (free_env_list(env));
	full_path = ft_strjoin(home, go_to + 1);
	env_oldpwd(env);
	if (chdir(full_path) == -1)
		return (print_error("minishell: cd: ", full_path, strerror(errno)),
			free(full_path));
	env_current_pwd(env);
	free(full_path);
}

void	bi_cd(char *go_to, t_env *env)
{
	while (*go_to && ft_isspace(*go_to))
		go_to++;
	if (!*go_to)
		return ;
	if (ft_strncmp(go_to, "~", 1) == 0)
		handle_tilde(go_to, env);
	else if (ft_strncmp(go_to, "..", 2) == 0)
	{
		env_oldpwd(env);
		if (!getcwd(NULL, 0))
			return (print_error("minishell: cd: ", "..", strerror(errno)));
		if (chdir(go_to) == -1)
			return (print_error("minishell: cd: ", go_to, strerror(errno)));
		env_current_pwd(env);
	}
	else if (ft_strncmp(go_to, ".", 1) == 0)
		env_oldpwd(env);
	else
	{
		env_oldpwd(env);
		if (chdir(go_to) == -1)
			return (print_error("minishell: cd: ", go_to, strerror(errno)));
		env_current_pwd(env);
	}
}

/* int	main(int ac, char **av, char **envp)
{
	t_env	*env_cpy;
	char	*path;
	t_env	*current;

	(void)ac;
	(void)av;
	env_cpy = copy_env(envp);
	if (!env_cpy)
		return (1);
	current = env_cpy;
	path = "/common_core";
	bi_cd(path, env_cpy);
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
			printf("oldpwd: %s\n", current->value);
		if (ft_strcmp(current->key, "PWD") == 0)
			printf("pwd: %s\n", current->value);
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
		if (ft_strncmp(input, "cd", 2) == 0)
		{
			bi_cd(input + 2, env);
			current = env;
			while (current)
			{
				if (ft_strcmp(current->key, "OLDPWD") == 0)
					printf("oldpwd: %s\n", current->value);
				if (ft_strcmp(current->key, "PWD") == 0)
					printf("pwd: %s\n", current->value);
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