/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:23:04 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/25 13:32:53 by grui-ant         ###   ########.fr       */
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
	if (key == M)
		map->is_expanded = 0;
	if (key == LEFT)
		map->player.rot_left = 0;
	if (key == RIGHT)
		map->player.rot_right = 0;
	return (0);
}
