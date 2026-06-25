/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:47:58 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/25 16:25:08 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	render_ceiling_floor(t_map *map, int x, t_wall *wall)
{
	int	y;

	y = 0;
	while (y < wall->draw_start)
	{
		img_pix_put(&map->data.img, x, y, rgb_to_int(map->ceiling_rgb[0], \
map->ceiling_rgb[1], map->ceiling_rgb[2]));
		y++;
	}
	y = wall->draw_end;
	while (y < HEIGHT)
	{
		img_pix_put(&map->data.img, x, y, rgb_to_int(map->floor_rgb[0], \
map->floor_rgb[1], map->floor_rgb[2]));
		y++;
	}
}

void	render_world(t_map *map)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ray_direction(&map->player, &map->ray, x);
		calculate_step_and_side_distance(map, &map->ray);
		dda(map, &map->ray);
		wall_distance(&map->ray);
		get_wall_height(map, &map->ray, &map->wall);
		render_ceiling_floor(map, x, &map->wall);
		render_wall(map, x);
		x++;
	}
}
