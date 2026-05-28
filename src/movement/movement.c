/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:16:39 by grui-ant          #+#    #+#             */
/*   Updated: 2026/05/28 19:03:15 by grui-ant         ###   ########.fr       */
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

void	player_movement(t_map *map)
{
	double mov_speed;
	int	y;
	int	x;
	
	y = map->player.posY;
	x = map->player.posX;
	mov_speed = 0.005;
	if (map->player.up)
	{
		if (map->grid[y][x] == '1')
			return ;
		map->player.posY -= mov_speed;
	}
	if (map->player.down)
	{
		if (map->grid[y + 1][x] == '1')
			return ;
		map->player.posY += mov_speed;
	}
	if (map->player.left)
	{
		if (map->grid[y][x] == '1')
			return ;
		map->player.posX -= mov_speed;
	}
	if (map->player.right)
	{
		if (map->grid[y][x + 1] == '1')
			return ;
		map->player.posX += mov_speed;
	}
}
