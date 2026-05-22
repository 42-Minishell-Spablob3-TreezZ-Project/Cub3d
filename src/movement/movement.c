/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:16:39 by grui-ant          #+#    #+#             */
/*   Updated: 2026/05/22 17:35:59 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_map *map)
{
	if (key == W)
	{
		map->player.up = 1;
		map->player.posY++;
		/* draw_square(&map->data.img, map->player.posX * TILE, map->player.posY * TILE, 13, 0x008000); */
		/* mlx_put_image_to_window(map->data.mlx, map->data.mlx_win, map->data.img.mlx_img, 0, 0); */
		printf("P Position: %f\n", map->player.posY);
	}
	if (key == S)
		map->player.down = 1;
	if (key == A)
		map->player.left = 1;
	if (key == D)
		map->player.right = 1;
	rendering_loop(map);
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
	return (0);
}

void	player_movement(t_map *map)
{
	int mov_speed = 2;

	if (map->player.up)
		map->player.posY++;
	if (map->player.down)
	{
		map->player.posY += mov_speed;
		printf("P Position: %f\n", map->player.posY);
	}
	/* if (player->left) */
	/* 	player->posX -= mov_speed; */
	/* if (player->right) */
	/* 	player->posX += mov_speed; */
}
