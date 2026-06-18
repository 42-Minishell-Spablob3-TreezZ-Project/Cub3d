/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:47:58 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/18 17:10:04 by grui-ant         ###   ########.fr       */
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

void	render_wall(t_map *map, int x)
{
	int		y;
	int		color;
	t_tex	*tex;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	char	*pixel;

	if (map->ray.side == 0)
	{
		if (map->ray.rayDirX > 0)
			tex = &map->west_tex;
		else
			tex = &map->east_tex;
	}
	else
	{
		if (map->ray.rayDirY > 0)
			tex = &map->north_tex;
		else
			tex = &map->south_tex;
	}
	if (map->ray.side == 0)
		wall_x = map->player.posY + map->ray.perpWallDist * map->ray.rayDirY;
	else
		wall_x = map->player.posX + map->ray.perpWallDist * map->ray.rayDirX;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (map->ray.side == 0 && map->ray.rayDirX > 0)
		tex_x = tex->width - tex_x - 1;
	if (map->ray.side == 1 && map->ray.rayDirY < 0)
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / map->wall.wall_height;
	tex_pos = (map->wall.draw_start - HEIGHT / 2 + map->wall.wall_height / 2) \
* step;
	y = map->wall.draw_start;
	while (y < map->wall.draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		pixel = tex->data + \
(tex_y * tex->size_line + tex_x * (tex->bpp / 8));
		color = *(unsigned int *)pixel;
		if (map->ray.side == 1)
			color = (color >> 1) & 8355711;
		img_pix_put(&map->data.img, x, y, color);
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
