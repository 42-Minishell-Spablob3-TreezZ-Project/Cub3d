/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:40:58 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/25 13:48:21 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_map(t_map *map)
{
	size_t	longest_line;
	int		size;
	char	*str;
	char	*tmp;
	int		i;

	longest_line = get_longest_line(map);
	i = 0;
	while (map->grid[i])
	{
		if (ft_strlen(map->grid[i]) < longest_line)
		{
			size = longest_line - ft_strlen(map->grid[i]);
			str = calloc((size + 1), sizeof(char));
			ft_memset(str, ' ', size);
			tmp = map->grid[i];
			map->grid[i] = ft_strjoin(tmp, str);
			free(tmp);
			free(str);
		}
		i++;
	}
}

int	fill_map_grid_array(t_map *map, int start)
{
	int		i;
	int		j;
	char	*line;

	i = start;
	while (map->map_array[i])
		i++;
	map->grid = ft_calloc((i - start) + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	j = 0;
	while (map->map_array[start])
	{
		line = ft_strtrim(map->map_array[start], "\n");
		map->grid[j] = ft_strdup(line);
		free(line);
		j++;
		start++;
	}
	map->grid[j] = NULL;
	return (start);
}

void	check_map_chars(char **map_grid, t_map *map)
{
	char	*valid_chars;
	int		i;
	int		j;

	valid_chars = " 01NSWE";
	i = 0;
	while (map_grid[i])
	{
		j = 0;
		while (map_grid[i][j])
		{
			if (!ft_strchr(valid_chars, map_grid[i][j]))
				error_free_exit(INVALID_CHAR, map);
			if (is_player(map_grid[i][j], map))
			{
				map->player.pos_y = (double)i + 0.5;
				map->player.pos_x = (double)j + 0.5;
				map->player_count++;
			}
			j++;
		}
		i++;
	}
	if (map->player_count != 1)
		error_free_exit(WRONG_NR_PLAYER, map);
}

char	**map_copy(t_map *map)
{
	int		i;
	char	**tmp;

	i = 0;
	while (map->grid[i])
		i++;
	tmp = ft_calloc((i + 1), sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (map->grid[i])
	{
		tmp[i] = ft_strdup(map->grid[i]);
		i++;
	}
	return (tmp);
}

int	parsing_map_grid(t_map *map, int start)
{
	int		result;
	char	**copy;
	int		i;

	map->is_map = 1;
	result = fill_map_grid_array(map, start);
	normalize_map(map);
	//edge_scan(map);
	set_map_dimensions(map);
	check_map_chars(map->grid, map);
	copy = map_copy(map);
	flood_fill(copy, map, map->player.pos_y, map->player.pos_x);
	i = 0;
	while (copy[i])
	{
		printf("%s\n", copy[i]);
		i++;
	}
	free_array(copy);
	return (result);
}
