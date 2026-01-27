/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:45:00 by juljin            #+#    #+#             */
/*   Updated: 2025/11/15 23:19:15 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*init_buffer(int fd, int clean)
{
	char	*buffer;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || clean)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	return (buffer);
}

static char	*get_line(char **stash)
{
	size_t	i;
	char	*new_stash;
	char	*line;

	if (!*stash || !**stash)
		return (free(*stash), *stash = NULL, NULL);
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
	{
		line = gnl_substr(*stash, 0, i + 1);
		new_stash = gnl_strdup(*stash + i + 1);
		free(*stash);
		*stash = new_stash;
		return (line);
	}
	line = gnl_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (line);
}

char	*get_next_line(int fd, int clean)
{
	char		*buffer;
	ssize_t		bytes_read;
	static char	*stash[OPEN_MAX];
	char		*temp;

	buffer = init_buffer(fd, clean);
	if (!buffer)
		return (free(stash[fd]), NULL);
	bytes_read = 1;
	while (!gnl_strchr(stash[fd], '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash[fd]), free(buffer), stash[fd] = NULL, NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = gnl_strjoin(stash[fd], buffer);
		if (!temp)
			return (free(stash[fd]), free(buffer), stash[fd] = NULL, NULL);
		free(stash[fd]);
		stash[fd] = temp;
	}
	return (free(buffer), get_line(&stash[fd]));
}

// #include <fcntl.h>

// int	main(int argc, char *av[])
// {
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	if (argc < 2)
// 		return (write(2, "no file\n", 8));
// 	i = 1;
// 	while (i < argc)
// 	{
// 		fd = open(av[i], O_RDONLY);
// 		if (fd == -1)
// 		{
// 			write(2, "Cannot read file.\n", 18);
// 			return (1);
// 		}
// 		line = get_next_line(fd);
// 		while (line != NULL)
// 		{
// 			printf("%s", line);
// 			free(line);
// 			line = get_next_line(fd);
// 		}
// 		close(fd);
// 		i++;
// 	}
// 	return (0);
// }
