/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_minimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 15:39:12 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 13:51:40 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the default PATH string */
char	*get_default_path(void)
{
	char	*path;

	path = ft_strjoin("PATH=/usr/local/sbin:/usr/local/bin:",
			"/usr/sbin:/usr/bin:/sbin:/bin");
	if (!path)
		return (NULL);
	return (path);
}

/* Sets an internal default `PATH` */
static void	set_path(t_env **head_ptr)
{
	t_env	*path_node;
	char	*default_path;

	default_path = get_default_path();
	if (!default_path)
		return ;
	path_node = env_new_node(default_path);
	if (!path_node)
		return ;
	free(default_path);
	path_node->is_exported = 0;
	env_add_back(head_ptr, path_node);
}

/* Sets the variables as `exported` */
static void	set_exported(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		current->is_exported = 1;
		current = current->next;
	}
}

/* Adds the default exported variables */
static int	add_exported(t_env **head_ptr)
{
	t_env	*node;
	char	*path;
	char	*pwd;

	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	pwd = ft_strjoin("PWD=", path);
	free(path);
	if (!pwd)
		return (0);
	node = env_new_node(pwd);
	free(pwd);
	if (!node)
		return (0);
	env_add_back(head_ptr, node);
	node = env_new_node("SHLVL=1");
	if (!node)
		return (0);
	env_add_back(head_ptr, node);
	node = env_new_node("_=/usr/bin/env");
	if (!node)
		return (0);
	env_add_back(head_ptr, node);
	return (1);
}

/* Creates a similar env as when `env -i` is ran at launch */
t_env	*minimal_env(void)
{
	t_env	*head;
	t_env	*oldpwd_node;

	head = NULL;
	set_path(&head);
	oldpwd_node = env_new_node("OLDPWD");
	if (!oldpwd_node)
		return (NULL);
	env_add_back(&head, oldpwd_node);
	if (!add_exported(&head))
	{
		if (head)
			free_env_list(head);
		return (NULL);
	}
	set_exported(head->next);
	head->empty_start = 1;
	return (head);
}
