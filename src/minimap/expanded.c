/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:08:07 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/18 17:17:38 by grui-ant         ###   ########.fr       */
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
//	render_minimap(map, size, 0x000000); //Clear small minimap
	render_minimap(map, (size * 2), 0x0000FF);
	draw_square(&map->data.img, map->player.posX * (size * 2), \
map->player.posY * (size * 2), (size * 2), 0x008000);
}

void	clear_expanded(t_map *map, int size)
{
	render_minimap(map, (size * 2), 0x000000);
	draw_square(&map->data.img, map->player.posX * (size * 2), \
map->player.posY * (size * 2), (size * 2), 0x000000);
}
