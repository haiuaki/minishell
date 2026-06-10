/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:20:24 by juljin            #+#    #+#             */
/*   Updated: 2026/04/07 02:41:54 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_BONUS_H
# define ENV_BONUS_H

# include "structs.h"

/* ------------------------------- INITIALIZE ------------------------------- */

t_env	*copy_env(char **envp);
t_env	*minimal_env(void);
char	*get_default_path(void);
void	handle_shlvl(t_shell *shell);

/* --------------------------------- UTILS ---------------------------------- */

t_env	*env_new_node(char *str);
void	env_add_back(t_env **head, t_env *new_node);
size_t	env_list_size(t_env *env);
char	*env_get_value(t_env *env, char *key);
void	env_set_value(t_env *env, char *key, char *new_value);

int		env_var_exists(t_env *env, const char *key);

char	**env_to_array(t_env *env);

/* ---------------------------------- FREE ---------------------------------- */

void	free_env_node(t_env *node);
void	free_env_list(t_env *head);

#endif
