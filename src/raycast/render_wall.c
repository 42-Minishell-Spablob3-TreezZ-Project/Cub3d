/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:07:45 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/25 16:41:11 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	wall_sides(t_map *map)
{
	double	wall_x;

	if (map->ray.side == 0)
		wall_x = map->player.pos_y + map->ray.perp_wall_dist * \
map->ray.ray_dir_y;
	else
		wall_x = map->player.pos_x + map->ray.perp_wall_dist * \
map->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

t_tex	*ray_sides(t_map *map, t_tex *tex)
{
	if (map->ray.side == 0)
	{
		if (map->ray.ray_dir_x > 0)
			tex = &map->west_tex;
		else
			tex = &map->east_tex;
	}
	else
	{
		if (map->ray.ray_dir_y > 0)
			tex = &map->north_tex;
		else
			tex = &map->south_tex;
	}
	return (tex);
}

void	print_wall(t_map *map, t_tex *tex, double tex_pos, \
int tex_x, double step, int x)
{
	int		y;
	int		tex_y;
	int		color;
	char	*pixel;

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

void	render_wall(t_map *map, int x)
{
	t_tex	*tex;
	int		tex_x;
	double	step;
	double	tex_pos;

	tex = NULL;
	tex = ray_sides(map, tex);
	tex_x = (int)(wall_sides(map) * tex->width);
	if (map->ray.side == 0 && map->ray.ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (map->ray.side == 1 && map->ray.ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / map->wall.wall_height;
	tex_pos = (map->wall.draw_start - HEIGHT / 2 + \
map->wall.wall_height / 2) * step;
	print_wall(map, tex, tex_pos, tex_x, step, x);
}
