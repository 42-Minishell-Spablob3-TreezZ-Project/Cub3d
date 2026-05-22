/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:57:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/22 11:31:08 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

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
	int x;
	int y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '1')
				draw_square(&map->data.img, x *TILE, y * TILE, TILE, 0x0000FF);
			else
				draw_square(&map->data.img, x *TILE, y * TILE, TILE, 0x000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->data.mlx, map->data.mlx_win, map->data.img.mlx_img, 0, 0);
}