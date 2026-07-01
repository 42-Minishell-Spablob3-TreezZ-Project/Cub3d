/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:57:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/07/01 13:16:49 by grui-ant         ###   ########.fr       */
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

int	obtain_x(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->grid[y][x])
		x++;
	return (x);
}

int	obtain_y(t_map *map)
{
	int	y;

	y = 0;
	while (map->grid[y])
		y++;
	return (y);
}

void	render_bg(t_map *map, t_specs specs)
{
	int	x;
	int	y;
	int	x_value;
	int	y_value;

	x_value = obtain_x(map);
	y_value = obtain_y(map);
	specs.color = 0x000000;
	y = 0;
	while (y < y_value)
	{
		x = 0;
		while (x < x_value)
		{
			draw_square(&map->data.img, x * specs.size, \
y * specs.size, specs);
			x++;
		}
		y++;
	}
}

void	render_highlight_bg(t_map *map, t_specs specs)
{
	int	x;
	int	y;
	int	x_value;
	int	y_value;

	x_value = obtain_x(map);
	y_value = obtain_y(map);
	specs.color = 0x880808;
	y = 0;
	while (y < y_value + 1)
	{
		x = 0;
		while (x < x_value + 1)
		{
			draw_square(&map->data.img, x * specs.size, \
y * specs.size, specs);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_map *map, t_specs specs)
{
	int	x;
	int	y;

	render_highlight_bg(map, specs);
	render_bg(map, specs);
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
