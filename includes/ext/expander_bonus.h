/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:51:06 by juljin            #+#    #+#             */
/*   Updated: 2026/04/07 02:41:01 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_BONUS_H
# define EXPANDER_BONUS_H

/* ------------------------------- STRUCTURE -------------------------------- */

typedef struct s_expand
{
	char	*val;
	char	*meta;
	char	*new_val;
	char	*sub;
	char	*key_val;
	size_t	keylen;
}			t_expand;

/* -------------------------------- EXPANDER -------------------------------- */

void	expander(t_shell *s);
void	expand_wildcards(t_token **tokens);
void	expand_variable(t_shell *s, t_expand *exp, size_t *i);
void	expand_tilde(t_env *env, t_expand *exp, size_t *i);
char	*expand_heredoc_string(t_shell *s, char *str);

/* --------------------------------- UTILS ---------------------------------- */

char	*join_and_free(char *s1, char *s2);
size_t	get_keylen(char *key, char *meta);
int		advance_until_var(t_expand *exp, size_t *i, size_t *j);
void	join_one_char(t_expand *exp, size_t *j);

/* ---------------------------- WILDCARD UTILS ------------------------------ */

int		wildcard_match(const char *pattern, const char *filename);
void	sort_matches(char **matches, size_t count);
void	free_matches_array(char **matches, size_t count);
t_token	*create_match_token(char *value, t_token *original);
char	**collect_matching_names(char *pattern, size_t *count);

#endif
