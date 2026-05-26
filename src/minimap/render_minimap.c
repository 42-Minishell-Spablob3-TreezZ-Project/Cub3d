/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:57:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/26 16:23:31 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	double	i;
	double	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			img_pix_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_map *map)
{
	int	x;
	int	y;
	int	size;

	size = 13;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			/* if (is_player(map->grid[y][x], map)) */
			/* { */
			/* 	draw_square(&map->data.img, (x * TILE) + (size / 2) + 3, (y * TILE) + (size / 2) + 3, size, 0x008000); */
			/* 	//draw_square(&map->data.img, map->player.dirX, map->player.dirY, 8, 0x800020); */
			/* } */
			if (map->grid[y][x] == '1')
				draw_square(&map->data.img, x, y, 1, 0x0000FF);
			x++;
		}
		y++;
	}
}
