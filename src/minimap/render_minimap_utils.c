/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 13:41:33 by grui-ant          #+#    #+#             */
/*   Updated: 2026/07/01 13:51:33 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img *img, int x, int y, t_specs specs)
{
	double	i;
	double	j;

	i = 0;
	while (i < (specs.size / 2))
	{
		j = 0;
		while (j < (specs.size / 2))
		{
			img_pix_put(img, x + j, y + i, 0x008000);
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
	specs.color = 0x2B2B2B;
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
