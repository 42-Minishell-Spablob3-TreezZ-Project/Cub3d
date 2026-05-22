/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 09:37:32 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/19 14:22:17 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_north_south_dir(t_map *map, char orientation)
{
	if (orientation == 'N')
	{
		map->player.dirY = -1;
		map->player.dirX = 0;
		map->player.planeY = 0;
		map->player.planeX = 0.66;
 	}
	else if (orientation == 'S')
	{
		map->player.dirY = 1;
		map->player.dirX = 0;
		map->player.planeY = 0;
		map->player.planeX = -0.66;
 	}
}

void	set_east_west_dir(t_map *map, char orientation)
{
	if (orientation == 'E')
	{
		map->player.dirY = 0;
		map->player.dirX = 1;
		map->player.planeY = 0.66;
		map->player.planeX = 0;
 	}
	else if (orientation == 'W')
	{
		map->player.dirY = 0;
		map->player.dirX = -1;
		map->player.planeY = -0.66;
		map->player.planeX = 0;
 	}
}

void	set_player_direction(t_map *map)
{	
	char	orientation;

	orientation = map->player.player_orientation;
	if(orientation == 'N' || orientation == 'S')
		set_north_south_dir(map, orientation);
	else if(orientation == 'E' || orientation == 'W')
		set_east_west_dir(map, orientation);
}
