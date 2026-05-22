/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:35 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/05 12:39:54 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_line(char *file_name)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**alloc_map_array(int size)
{
	char	**map_array;

	map_array = malloc(sizeof(char *) * (size + 1));
	if (!map_array)
		return (NULL);
	return (map_array);
}

void	fill_map_array(char *file_name, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit (1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->map_array[i] = ft_strdup(line);
		if (!map->map_array[i])
			exit (1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map->map_array[i] = NULL;
	close(fd);
}

void	map_load(char *file_name, t_map *map)
{
	int	size;

	size = ft_count_line(file_name);
	if (size == 0)
	{
		free(map);
		error_exit(EMPTY_FILE);
	}
	map->map_array = alloc_map_array(size);
	if (!map->map_array)
		exit (1);
	fill_map_array(file_name, map);
}
