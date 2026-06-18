/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 09:37:32 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/18 16:54:22 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_direction(t_map *map)
{
	char	orientation;

	orientation = map->player.player_orientation;
	if (orientation == 'N')
		map->player.player_angle = -PI / 2;
	if (orientation == 'S')
		map->player.player_angle = PI / 2;
	if (orientation == 'E')
		map->player.player_angle = 0;
	if (orientation == 'W')
		map->player.player_angle = PI;
	map->player.dirX = cos(map->player.player_angle);
	map->player.dirY = sin(map->player.player_angle);
	map->player.planeX = -sin(map->player.player_angle) * 0.66;
	map->player.planeY = cos(map->player.player_angle) * 0.66;
}
