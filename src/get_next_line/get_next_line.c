/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:18 by joapedro          #+#    #+#             */
/*   Updated: 2026/04/29 10:26:22 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_next_line(int fd)
{
	int			bytes_read;
	static char	read_buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	bytes_read = 1;
	line = gnl_strjoin(line, read_buffer);
	while (!gnl_strchr(read_buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1 || read_buffer[0] == 0)
		{
			free(line);
			shift(read_buffer);
			return (NULL);
		}
		if (!bytes_read)
			break ;
		read_buffer[bytes_read] = '\0';
		line = gnl_strjoin(line, read_buffer);
	}
	shift(read_buffer);
	return (line);
}
