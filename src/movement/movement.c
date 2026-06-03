/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:16:39 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/02 19:28:05 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_game(t_map *map)
{
	mlx_loop_end(map->data.mlx);
}

int	key_press(int key, t_map *map)
{
	if (key == W)
		map->player.up = 1;
	if (key == S)
		map->player.down = 1;
	if (key == A)
		map->player.left = 1;
	if (key == D)
		map->player.right = 1;
	if (key == M)
		map->is_expanded++;
	if (key == LEFT)
		map->player.rot_left = 1;
	if (key == RIGHT)
		map->player.rot_right = 1;
	if (key == ESC)	
		exit_game(map);
	return (0);
}

int	key_release(int key, t_map *map)
{
	if (key == W)
		map->player.up = 0;
	if (key == S)
		map->player.down = 0;
	if (key == A)
		map->player.left = 0;
	if (key == D)
		map->player.right = 0;
//	if (key == M)
//		map->is_expanded = 0;
	if (key == LEFT)
		map->player.rot_left = 0;
	if (key == RIGHT)
		map->player.rot_right = 0;
	return (0);
}

void	move_forward(t_map *map, t_player *player, double cos_a, double sin_a)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = player->posX + cos_a * move_speed;
	new_y = player->posY + sin_a * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	move_backwards(t_map *map, t_player *player, double cos_a, double sin_a)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = player->posX - cos_a * move_speed;
	new_y = player->posY - sin_a * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	move_left(t_map *map, t_player *player, double cos_a, double sin_a)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = player->posX + sin_a * move_speed;
	new_y = player->posY - cos_a * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	move_right(t_map *map, t_player *player, double cos_a, double sin_a)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.02;
	new_x = player->posX - sin_a * move_speed;
	new_y = player->posY + cos_a * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	rotate_player(t_map *map, t_player	*player)
{
	(void)player;
	if (map->player.rot_left == 1)
	{
		map->player.player_angle -= ROTATE_SPEED;
		map->player.dirX = cos(map->player.player_angle);
		map->player.dirY = sin(map->player.player_angle);
		map->player.planeX = -sin(map->player.player_angle) * 0.66;
		map->player.planeY = cos(map->player.player_angle) * 0.66;
	}
	if (map->player.rot_right == 1)
	{
		map->player.player_angle += ROTATE_SPEED;
		map->player.dirX = cos(map->player.player_angle);
		map->player.dirY = sin(map->player.player_angle);
		map->player.planeX = -sin(map->player.player_angle) * 0.66;
		map->player.planeY = cos(map->player.player_angle) * 0.66;
	}
}

void	player_movement(t_map *map)
{
	double cos_a;
	double sin_a;
	
	rotate_player(map, &map->player);
	cos_a = cos(map->player.player_angle);
	sin_a = sin(map->player.player_angle);
	if (map->player.up == 1)
		move_forward(map, &map->player, cos_a, sin_a);
	if (map->player.down == 1)
		move_backwards(map, &map->player, cos_a, sin_a);
	if (map->player.left == 1)
		move_left(map, &map->player, cos_a, sin_a);
	if (map->player.right == 1)
		move_right(map, &map->player, cos_a, sin_a);
}
