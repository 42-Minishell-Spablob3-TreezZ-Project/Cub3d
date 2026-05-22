/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:20:01 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/19 12:27:23 by joapedro         ###   ########.fr       */
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
	while(map->grid[i])
		i++;
	map->height = i;
	map->width = ft_strlen(map->grid[0]);
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