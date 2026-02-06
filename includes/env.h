/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:20:24 by juljin            #+#    #+#             */
/*   Updated: 2026/02/05 17:00:56 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "includes.h"

/* -------------------------------- STRUCTURE ------------------------------- */

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_exported;
	struct s_env	*next;
}					t_env;

/* ------------------------------- INITIALIZE ------------------------------- */

t_env	*copy_env(char **envp);

/* --------------------------------- UTILS ---------------------------------- */

t_env	*env_new_node(char *str);
void	env_add_back(t_env **head, t_env *new_node);

/* ---------------------------------- FREE ---------------------------------- */

void	free_env_node(t_env *node);
void	free_env_list(t_env *head);

#endif