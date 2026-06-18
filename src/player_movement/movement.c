/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:16:39 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/18 14:22:36 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_horizontal(t_map *map, t_player *player, double cos_a, \
double sin_a)
{
	double	new_x;
	double	new_y;

	if (map->player.up == 1)
	{
		new_x = player->posX + cos_a * SPEED;
		new_y = player->posY + sin_a * SPEED;
		if (map->grid[(int)player->posY][(int)new_x] != '1')
			player->posX = new_x;
		if (map->grid[(int)new_y][(int)player->posX] != '1')
			player->posY = new_y;
	}
	if (map->player.down == 1)
	{
		new_x = player->posX - cos_a * SPEED;
		new_y = player->posY - sin_a * SPEED;
		if (map->grid[(int)player->posY][(int)new_x] != '1')
			player->posX = new_x;
		if (map->grid[(int)new_y][(int)player->posX] != '1')
			player->posY = new_y;
	}
}

void	move_sideways(t_map *map, t_player *player, double cos_a, double sin_a)
{
	double	new_x;
	double	new_y;

	if (map->player.left == 1)
	{
		new_x = player->posX + sin_a * SPEED;
		new_y = player->posY - cos_a * SPEED;
		if (map->grid[(int)player->posY][(int)new_x] != '1')
			player->posX = new_x;
		if (map->grid[(int)new_y][(int)player->posX] != '1')
			player->posY = new_y;
	}
	if (map->player.right == 1)
	{
		new_x = player->posX - sin_a * SPEED;
		new_y = player->posY + cos_a * SPEED;
		if (map->grid[(int)player->posY][(int)new_x] != '1')
			player->posX = new_x;
		if (map->grid[(int)new_y][(int)player->posX] != '1')
			player->posY = new_y;
	}
}

void	rotate_player(t_map *map)
{
	if (map->player.rot_left == 1)
		map->player.player_angle -= ROTATE_SPEED;
	if (map->player.rot_right == 1)
		map->player.player_angle += ROTATE_SPEED;
	map->player.dirX = cos(map->player.player_angle);
	map->player.dirY = sin(map->player.player_angle);
	map->player.planeX = -sin(map->player.player_angle) * 0.66;
	map->player.planeY = cos(map->player.player_angle) * 0.66;
}

void	player_movement(t_map *map)
{
	double	cos_a;
	double	sin_a;

	rotate_player(map);
	cos_a = cos(map->player.player_angle);
	sin_a = sin(map->player.player_angle);
	move_horizontal(map, &map->player, cos_a, sin_a);
	move_sideways(map, &map->player, cos_a, sin_a);
}
