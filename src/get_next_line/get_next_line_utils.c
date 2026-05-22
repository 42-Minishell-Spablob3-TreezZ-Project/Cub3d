/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:07 by joapedro          #+#    #+#             */
/*   Updated: 2026/04/29 10:33:16 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	gl_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] && s[i] == '\n')
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int		len;
	int		i;

	len = gl_strlen(s);
	c = (unsigned char)c;
	i = 0;
	while (i <= len)
	{
		if (s[i] == c)
			return ((char *)s);
		i++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*gnl_strjoin(char *line, char *read_buffer)
{
	char	*str;
	int		i;
	int		j;

	str = malloc((gl_strlen(line) + gl_strlen(read_buffer) + 1) * sizeof(char));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (line && line[i])
	{
		str[i] = line[i];
		i++;
	}
	j = 0;
	while (j < gl_strlen(read_buffer))
	{
		str[i + j] = read_buffer[j];
		j++;
	}
	str[i + j] = '\0';
	free(line);
	return (str);
}

void	shift(char *read_buffer)
{
	int	i;
	int	j;

	i = 0;
	while (read_buffer[i] && read_buffer[i] != '\n')
		i++;
	if (read_buffer[i] == '\n')
		i++;
	j = 0;
	while (read_buffer[i + j])
	{
		read_buffer[j] = read_buffer[i + j];
		j++;
	}
	read_buffer[j] = '\0';
}
