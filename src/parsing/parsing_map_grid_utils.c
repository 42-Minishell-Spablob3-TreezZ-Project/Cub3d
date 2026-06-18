/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:20:01 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/18 17:03:37 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c, t_map *map)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		map->player.player_orientation = c;
		return (1);
	}
	return (0);
}

int	get_longest_line(t_map *map)
{
	int	i;
	int	max;
	int	len;

	max = 0;
	i = 0;
	while (map->grid[i])
	{
		len = ft_strlen(map->grid[i]);
		if (max < len)
			max = len;
		i++;
	}
	return (max);
}

void	set_map_dimensions(t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i])
		i++;
	map->height = i;
	map->width = ft_strlen(map->grid[0]);
}

void	flood_fill(char **grid, t_map *map, int y, int x)
{
//	char *valid = "1FNSEW";
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		error_free_exit(FLOOD_FILL, map);
	if (grid[y][x] == ' ')
		error_free_exit(FLOOD_FILL, map);
	if (grid[y][x] == '1' || grid[y][x] == 'F')
		return ;
	grid[y][x] = 'F';
	flood_fill(grid, map, y - 1, x);
	flood_fill(grid, map, y + 1, x);
	flood_fill(grid, map, y, x - 1);
	flood_fill(grid, map, y, x + 1);
}

/* void	edge_scan(t_map *map)
{
	char	*valid_chars;
	int		i;
	int		j;
	int		len;
	
	valid_chars = " 1";
	i = 0;
	while (map->grid[i])
		i++;
	len = i;
	i =0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (i == 0 && !ft_strchr(valid_chars, map->grid[i][j]))
				error_free_exit(INVALID_CHAR, map);
			else if (i == len && !ft_strchr(valid_chars, map->grid[i][j]))
				error_free_exit(INVALID_CHAR, map);
			j++;
		}
		i++;
	}
}
 */
