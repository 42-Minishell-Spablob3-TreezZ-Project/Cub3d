/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:08:07 by grui-ant          #+#    #+#             */
/*   Updated: 2026/07/01 13:53:58 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	size_scales(int size)
{
	if (size < 25)
		return (75);
	if (size >= 25 && size < 50)
		return (35);
	if (size >= 50 && size < 75)
		return (28);
	if (size >= 75 && size < 100)
		return (20);
	if (size >= 100)
		return (10);
	return (0);
}

int	check_dims(t_map *map)
{
	int	x;
	int	y;
	int	size;

	size = 0;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
			x++;
		if (x > size)
			size = x;
		y++;
	}
	if (y > x)
		size = y;
	size = size_scales(size);
	return (size);
}

void	expanded_minimap(t_map *map, int size)
{
	t_specs	specs;

	specs.size = size * 2;
	specs.color = 0x0000FF;
	render_minimap(map, specs);
	draw_player(&map->data.img, map->player.pos_x * (size * 2), \
map->player.pos_y * (size * 2), specs);
}

void	clear_expanded(t_map *map, int size)
{
	t_specs	specs;

	specs.size = size * 2;
	specs.color = 0x000000;
	render_minimap(map, specs);
	draw_square(&map->data.img, map->player.pos_x * (size * 2), \
map->player.pos_y * (size * 2), specs);
}
