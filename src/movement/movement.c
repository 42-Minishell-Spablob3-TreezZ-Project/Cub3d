/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 15:16:39 by grui-ant          #+#    #+#             */
/*   Updated: 2026/05/22 15:57:22 by grui-ant         ###   ########.fr       */
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

void	player_movement(t_player *player)
{
	int mov_speed = 2;

	if (player->up)
		player->posY -= mov_speed;
	if (player->down)
		player->posY += mov_speed;
	if (player->left)
		player->posX -= mov_speed;
	if (player->right)
		player->posX += mov_speed;
}
