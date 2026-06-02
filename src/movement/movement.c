/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:16:39 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/02 18:04:14 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (0);
}

void	move_forward(t_map *map, t_player *player)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.03;
	new_x = player->posX + player->dirX * move_speed;
	new_y = player->posY + player->dirY * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	move_backwards(t_map *map, t_player *player)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.03;
	new_x = player->posX - player->dirX * move_speed;
	new_y = player->posY - player->dirY * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	move_left(t_map *map, t_player *player)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.03;
	new_x = player->posX - player->dirX * move_speed;
	new_y = player->posY + player->dirY * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	move_right(t_map *map, t_player *player)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = 0.03;
	new_x = player->posX + player->dirX * move_speed;
	new_y = player->posY - player->dirY * move_speed;

	if (map->grid[(int)player->posY][(int)new_x] != '1')
		player->posX = new_x;
	if (map->grid[(int)new_y][(int)player->posX] != '1')
		player->posY = new_y;
}

void	player_movement(t_map *map)
{
	if (map->player.up == 1)
		move_forward(map, &map->player);
	if (map->player.down == 1)
		move_backwards(map, &map->player);
	if (map->player.left == 1)
		move_left(map, &map->player);
	if (map->player.right == 1)
		move_right(map, &map->player);
}
