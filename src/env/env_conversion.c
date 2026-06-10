/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:53:50 by sopelet           #+#    #+#             */
/*   Updated: 2026/04/14 13:51:42 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Converts a `t_env` node from the list to an array in the key=value format */
static char	*create_line(t_env *env)
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

/* 
 * Checks if the `empty_start` flag is set.
 * If yes, allocates one extra string to be able to set a default internal path
 * for the program to be able to run commands as bash would when ran with
 * `env -i bash --posix`.
 * If not, allocates the regular amount of exported variables with set values.
 */
static int	init_env_array(t_env *env, char ***arr, size_t *i)
{
	if (env->empty_start)
	{
		*arr = malloc(sizeof(char *) * (env_list_size(env) + 2));
		if (!*arr)
			return (0);
		*arr[0] = get_default_path();
		if (!*arr[0])
			return (ft_free_array(*arr), 0);
		*i = 1;
	}
	else
	{
		*arr = malloc(sizeof(char *) * (env_list_size(env) + 1));
		if (!*arr)
			return (0);
		*i = 0;
	}
	return (1);
}

/* 
 * Converting the env_list to an array of strings
 * Sent to the array only if is_exported = 1
 * Needed to call execve() with an env that may change at runtime
 */
char	**env_to_array(t_env *env)
{
	t_env	*current;
	size_t	i;
	char	**arr;

	if (!init_env_array(env, &arr, &i))
		return (NULL);
	current = env;
	while (current)
	{
		if (current->is_exported)
		{
			if (!current->value)
			{
				current = current->next;
				continue ;
			}
			arr[i] = create_line(current);
			if (!arr[i])
				return (ft_free_array(arr), NULL);
			i++;
		}
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}
/* 
int	main(int ac, char **av, char **envp)
{
	t_env	*env_cp;
	char	**env_array;
	int		i;
	t_env	*export;

	(void)ac;
	(void)av;
	i = 0;
	env_cp = copy_env(envp);
	if (!env_cp)
		return (1);
	export = env_new_node("HOLA=GENTE");
	export->is_exported = 1;
	env_add_back(&env_cp, export);
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
