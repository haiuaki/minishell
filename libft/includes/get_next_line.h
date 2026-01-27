/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:45:02 by juljin            #+#    #+#             */
/*   Updated: 2025/11/15 23:18:43 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h> // for size_t type
# include <stdlib.h> // for malloc(), free() & NULL
# include <unistd.h> // for read()
# include <limits.h> // for OPEN_MAX

/* ----------------------------- IF NOT DEFINED ----------------------------- */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

/* ----------------------------- GET NEXT LINE ------------------------------ */

char	*get_next_line(int fd, int clean);

/* ---------------------------- HELPER FUNCTIONS ---------------------------- */

size_t	gnl_strlen(char *s);
char	*gnl_strdup(char *s);
char	*gnl_strjoin(char *stash, char *buffer);
char	*gnl_substr(char *s, unsigned int start, size_t len);
char	*gnl_strchr(char *s, int c);

#endif