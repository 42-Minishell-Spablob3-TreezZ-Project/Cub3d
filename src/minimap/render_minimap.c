/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:57:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/30 15:44:25 by grui-ant         ###   ########.fr       */
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

void	draw_square(t_img *img, int x, int y, t_specs specs)
{
	double	i;
	double	j;

	i = 0;
	while (i < specs.size)
	{
		j = 0;
		while (j < specs.size)
		{
			img_pix_put(img, x + j, y + i, specs.color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_map *map, t_specs specs)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '1')
				draw_square(&map->data.img, x * specs.size, \
y * specs.size, specs);
			x++;
		}
		y++;
	}
}
