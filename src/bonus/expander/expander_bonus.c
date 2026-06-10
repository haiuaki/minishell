/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:02:20 by juljin            #+#    #+#             */
/*   Updated: 2026/04/07 01:24:56 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * Checks if a `prev` node exists and if it's a heredoc operator (<<)
 * If yes, skips the current node, that is the DELIMITER of the heredoc,
 * preventing its expansion.
 * e.g.: `cat << $USER`, the DELIMITER is the string literal `$USER`.
 */
static int	prev_is_heredoc(t_token **curr_ptr, t_token **prev_ptr)
{
	if (*prev_ptr && (*prev_ptr)->type == TK_HEREDOC)
	{
		*prev_ptr = *curr_ptr;
		*curr_ptr = (*curr_ptr)->next;
		return (1);
	}
	return (0);
}

/* 
 * Helper function to initialize the `t_expand` struct by preparing the variable
 * expansion and retrieving the token's value and information.
 */
static int	init_expand_struct(t_token *current, t_expand *exp)
{
	exp->new_val = ft_strdup("");
	if (!exp->new_val)
		return (0);
	exp->val = current->value;
	exp->meta = current->meta;
	return (1);
}

/*
 * Replaces the token's old value with the new expanded value and
 * advances the token list.
 */
static void	update_and_advance_token(t_token **current, t_expand *exp)
{
	free((*current)->value);
	(*current)->value = exp->new_val;
	*current = (*current)->next;
}

/*
 * Expands all variables in the current token value.
 * Iterates through the string, finds variables, and expands them.
 */
static void	expand_token_variables(t_shell *s, t_expand *exp)
{
	size_t	i;
	size_t	j;

	i = 0;
	expand_tilde(s->env_list, exp, &i);
	while (exp->val[i])
	{
		if (!advance_until_var(exp, &i, &j))
			break ;
		i = j + 1;
		exp->keylen = get_keylen(&exp->val[i], &exp->meta[i]);
		if (exp->keylen > 0 && exp->meta[j] != exp->meta[i])
			exp->keylen = 0;
		if (exp->keylen > 0)
			expand_variable(s, exp, &i);
		else
			join_one_char(exp, &j);
	}
}

/* 
 * Advances through the token list created from the user's input
 * and look for any environment variables.
 * If found, expand them to their value.
 * Skips heredoc delimiters (tokens after <<) to preserve literal matching.
 */
void	expander(t_shell *s)
{
	t_token		*current;
	t_token		*prev;
	t_expand	exp;

	current = s->tokens;
	prev = NULL;
	while (current)
	{
		if (prev_is_heredoc(&current, &prev))
			continue ;
		if (!init_expand_struct(current, &exp))
			break ;
		expand_token_variables(s, &exp);
		prev = current;
		update_and_advance_token(&current, &exp);
	}
	expand_wildcards(&s->tokens);
}
/*
int	main(int ac, char **av, char **envp)
{
	t_shell	*s;
	t_token	*tmp;
	char	*input;
	size_t	i;

	(void)ac;
	(void)av;
	s = ft_calloc(1, sizeof(t_shell));
	if (!s)
		return (1);
	s->env_list = copy_env(envp);
	if (!s->env_list)
	{
		s->env_list = minimal_env();
		if (!s->env_list)
			return (free(s), 1);
	}
	while (1)
	{
		i = 0;
		s->tokens = NULL;
		input = readline(PROMPT);
		if (!input)
			return (free_env_list(s->env_list), 1);
		if (input && *input)
		{
			add_history(input);
			s->tokens = tokenizer(input);
			if (!s->tokens)
				return (free(input), free_env_list(s->env_list), 1);
			tmp = s->tokens;
			while (tmp)
			{
				printf("[%zu] %s\n", i, tmp->value);
				printf("[meta] %s\n", tmp->meta);
				tmp = tmp->next;
				i++;
			}
			i = 0;
			expander(&s->tokens, s->env_list);
			tmp = s->tokens;
			while (tmp)
			{
				printf("expanded [%zu] %s\n", i, tmp->value);
				tmp = tmp->next;
				i++;
			}
		}
	//	if (ft_strncmp(input, "export", 6) == 0)
	//		bi_export(tokens, &env);
	//	if (ft_strcmp(input, "env") == 0)
	//		bi_env(env);
	//	if (ft_strncmp(input, "unset", 5) == 0)
	//		bi_unset(tokens, &env);
		free(input);
		free_token_list(s->tokens);
	}
	free_env_list(s->env_list);
	return (0);
}
*/
