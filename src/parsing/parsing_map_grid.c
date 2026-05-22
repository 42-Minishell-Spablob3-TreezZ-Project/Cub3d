/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:40:58 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/19 12:27:51 by joapedro         ###   ########.fr       */
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
	int	i;
	int	j;
	char	*line;

	i = start;
	while (map->map_array[i])
		i++;
	map->grid = ft_calloc((i - start) + 1, sizeof(char *));
	if(!map->grid)
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
	while(map_grid[i])
	{
		j = 0;
		while (map_grid[i][j])
		{
			if(!ft_strchr(valid_chars, map_grid[i][j]))
				error_free_exit(INVALID_CHAR,map);
			if(is_player(map_grid[i][j], map))
			{
				map->player.posY = (double)i + 0.5; //set player position in the center
				map->player.posX = (double)j + 0.5;
				map->player_count++;
			}
			j++;
		}
		i++;
	}
	if (map->player_count != 1)
		error_free_exit(DUPLICATE_PLAYER,map);
}

void	flood_fill(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		error_free_exit(FLOOD_FILL, map);
	if (map->grid[y][x] == ' ')
		error_free_exit(FLOOD_FILL, map);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'F')
		return;
	map->grid[y][x] = 'F';
	flood_fill(map, y - 1, x);
	flood_fill(map, y + 1, x);
	flood_fill(map, y, x - 1);
	flood_fill(map, y, x + 1);
}

int	parsing_map_grid(t_map *map, int start)
{
	int	result;
	
	map->is_map = 1; //indicar que o map_grid comecou.
	result = fill_map_grid_array(map, start); //preencher grid e retornar quantas vezes o i andou.
	normalize_map(map); //preparar mapa para floodfill (rectangulizar)
	//edge_scan(map);
	set_map_dimensions(map);
	check_map_chars(map->grid, map); // checkar caracteres validos
	flood_fill(map, map->player.posY, map->player.posX);
	int i = 0;
	while (map->grid[i])
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
	return (result);
}
