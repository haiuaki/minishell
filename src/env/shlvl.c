/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:05:34 by juljin            #+#    #+#             */
/*   Updated: 2026/03/27 19:02:58 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Helper function to check if the value of the `SHlVL` env variable
 * is valid.
 * The value can start with a positive (+) or negative (-) sign
 * and the following characters must be digits.
 */
static int	is_valid_number(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/* 
 * Returns the value of the SHLVL depending on if :
 * the `SHLVL` variable doesn't exist / has no value / is invalid : returns 1
 * the value is negative : returns 0
 * the value is valid and the shell hasn't started with `env -i` : increments
 * If the shell started with an empty environment, a minimal env is set and
 * the SHLVL's value is 1.
 */
static int	compute_shlvl_value(t_shell *s, char *shlvl_val)
{
	int	shlvl_num;

	if (!shlvl_val || !is_valid_number(shlvl_val))
		return (1);
	shlvl_num = ft_atoi(shlvl_val);
	if (shlvl_num < 0)
		return (0);
	if (!s->env_list->empty_start)
		shlvl_num++;
	return (shlvl_num);
}

/* 
 * Create a default `SHLVL` environment variable in the `t_env` list.
 * This variable always exists whenever a shell is executed.
 */
static void	create_default_shlvl(t_shell *s)
{
	t_env	*new_node;

	new_node = env_new_node("SHLVL=1");
	if (!new_node)
		return ;
	env_add_back(&s->env_list, new_node);
}

/*
 * Handles the `SHLVL` environment variable update whenever
 * the program is executed inside itself.
 * In case the value of `SHLVL` in the parent process is
 * invalid (e.g. SHLVL=- ; SHLVL=+ ; SHLVL=1a)
 * The `SHLVL` value will be set to 1 in the child process.
 * If the value is a negative value, the SHLVL's value becomes 0.
 * Else if the program is first ran with an empty environment,
 * the value is manually set it with the minimal environment.
 */
void	handle_shlvl(t_shell *s)
{
	int		shlvl_num;
	char	*shlvl_val;
	char	*new_shlvl_val;

	if (env_var_exists(s->env_list, "SHLVL"))
	{
		shlvl_val = env_get_value(s->env_list, "SHLVL");
		shlvl_num = compute_shlvl_value(s, shlvl_val);
		new_shlvl_val = ft_itoa(shlvl_num);
		if (!new_shlvl_val)
		{
			free(shlvl_val);
			return ;
		}
		env_set_value(s->env_list, "SHLVL", new_shlvl_val);
		free(shlvl_val);
		free(new_shlvl_val);
	}
	else
		create_default_shlvl(s);
}
