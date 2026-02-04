/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:42:53 by juljin            #+#    #+#             */
/*   Updated: 2026/02/01 16:07:04 by juljin           ###   ########.fr       */
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
