/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:53:50 by sopelet           #+#    #+#             */
/*   Updated: 2026/02/05 17:47:17 by sopelet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(t_env *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

// Convert a node of env_list to an array in the key=value format
char	*create_line(t_env *env)
{
	char	*key;
	char	*line;

	key = ft_strjoin(env->key, "=");
	if (!key)
		return (NULL);
	line = ft_strjoin(key, env->value);
	if (!line)
		return (free(key), NULL);
	free(key);
	return (line);
}

/* Converting the env_list to an array of strings
Needed to call execve() with an env that may change at runtime */
char	**env_to_array(t_env *env)
{
	t_env	*current;
	size_t	i;
	char	**res;

	if (!env)
		return (NULL);
	res = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!res)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		res[i] = create_line(current);
		if (!res[i])
			return (ft_free_array(res), NULL);
		current = current->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
/* 
int	main(int ac, char **av, char **envp)
{
	t_env	*env_cp;
	char	**env_array;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	env_cp = copy_env(envp);
	if (!env_cp)
		return (1);
	env_array = env_to_array(env_cp);
	while (env_array[i])
	{
		printf("%s\n", env_array[i]);
		i++;
	}
	ft_free_array(env_array);
	free_env_list(env_cp);
	return (0);
}
 */