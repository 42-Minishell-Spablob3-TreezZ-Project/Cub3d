/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:16:39 by grui-ant          #+#    #+#             */
/*   Updated: 2026/07/14 11:52:53 by joapedro         ###   ########.fr       */
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
		new_x = player->pos_x + cos_a * SPEED;
		new_y = player->pos_y + sin_a * SPEED;
		if (map->grid[(int)player->pos_y][(int)new_x] != '1')
			player->pos_x = new_x;
		if (map->grid[(int)new_y][(int)player->pos_x] != '1')
			player->pos_y = new_y;
	}
	if (map->player.down == 1)
	{
		new_x = player->pos_x - cos_a * SPEED;
		new_y = player->pos_y - sin_a * SPEED;
		if (map->grid[(int)player->pos_y][(int)new_x] != '1')
			player->pos_x = new_x;
		if (map->grid[(int)new_y][(int)player->pos_x] != '1')
			player->pos_y = new_y;
	}
}

void	move_sideways(t_map *map, t_player *player, double cos_a, double sin_a)
{
	double	new_x;
	double	new_y;

	if (map->player.left == 1)
	{
		new_x = player->pos_x + sin_a * SPEED;
		new_y = player->pos_y - cos_a * SPEED;
		if (map->grid[(int)player->pos_y][(int)new_x] != '1')
			player->pos_x = new_x;
		if (map->grid[(int)new_y][(int)player->pos_x] != '1')
			player->pos_y = new_y;
	}
	if (map->player.right == 1)
	{
		new_x = player->pos_x - sin_a * SPEED;
		new_y = player->pos_y + cos_a * SPEED;
		if (map->grid[(int)player->pos_y][(int)new_x] != '1')
			player->pos_x = new_x;
		if (map->grid[(int)new_y][(int)player->pos_x] != '1')
			player->pos_y = new_y;
	}
}

void	rotate_player(t_map *map)
{
	if (map->player.rot_left == 1)
		map->player.player_angle -= ROTATE_SPEED;
	if (map->player.rot_right == 1)
		map->player.player_angle += ROTATE_SPEED;
	map->player.dir_x = cos(map->player.player_angle);
	map->player.dir_y = sin(map->player.player_angle);
	map->player.plane_x = -sin(map->player.player_angle) * 0.66;
	map->player.plane_y = cos(map->player.player_angle) * 0.66;
}

void	player_movement(t_map *map)
{
	double	cos_a;
	double	sin_a;

	rotate_player(map);
	cos_a = map->player.dir_x;
	sin_a = map->player.dir_y;
	move_horizontal(map, &map->player, cos_a, sin_a);
	move_sideways(map, &map->player, cos_a, sin_a);
}
