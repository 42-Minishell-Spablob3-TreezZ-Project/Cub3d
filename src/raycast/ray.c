/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:54:40 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/25 16:27:56 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_direction(t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = (2.0 * x / WIDTH) - 1.0;
	ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
}

void	calculate_step_and_side_distance(t_map *map, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (map->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - map->player.pos_x) \
* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (map->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - map->player.pos_y) \
* ray->delta_dist_y;
	}
}

void	dda(t_map *map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	get_wall_height(t_map *map, t_ray *ray, t_wall *wall)
{
	(void)map;
	wall->wall_height = (int)(HEIGHT / ray->perp_wall_dist);
	wall->draw_start = -wall->wall_height / 2 + HEIGHT / 2;
	wall->draw_end = wall->wall_height / 2 + HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
}
