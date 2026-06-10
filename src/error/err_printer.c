/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:42:53 by juljin            #+#    #+#             */
/*   Updated: 2026/04/14 14:42:51 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function for printing error messages and avoid buffering issues */
void	print_error(const char *prefix, const char *name, const char *msg)
{
	char	buffer[1024];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (prefix[j] && i < 1020)
		buffer[i++] = prefix[j++];
	j = 0;
	while (name[j] && i < 1020)
		buffer[i++] = name[j++];
	buffer[i++] = ':';
	buffer[i++] = ' ';
	j = 0;
	while (msg[j] && i < 1020)
		buffer[i++] = msg[j++];
	buffer[i++] = '\n';
	buffer[i] = '\0';
	write(2, buffer, i);
}

/* Helper for printing operator error messages and avoid buffering issues */
void	print_error_op(const char *msg, const char *name)
{
	char	buffer[1024];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (msg[j] && i < 1020)
		buffer[i++] = msg[j++];
	j = 0;
	buffer[i++] = '`';
	j = 0;
	while (name[j] && i < 1020)
		buffer[i++] = name[j++];
	buffer[i++] = '\'';
	buffer[i++] = '\n';
	buffer[i] = '\0';
	write(2, buffer, i);
}

/*
 * Print key error for `export` and `unset` builtins.
 * Used when an argument is not a valid identifier.
 * Format: "<cmd>: `<arg>': not a valid identifier"
 */
void	print_key_error(char *cmd, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
