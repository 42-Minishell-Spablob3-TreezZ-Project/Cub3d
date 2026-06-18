/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:54:40 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/18 16:25:53 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_direction(t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = (2.0 * x / WIDTH) - 1.0;
	ray->rayDirX = player->dirX + player->planeX * camera_x;
	ray->rayDirY = player->dirY + player->planeY * camera_x;
	ray->mapX = (int)player->posX;
	ray->mapY = (int)player->posY;
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->deltaDistX = fabs(1 / ray->rayDirX);
}

void	calculate_step_and_side_distance(t_map *map, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (map->player.posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - map->player.posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (map->player.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - map->player.posY) * ray->deltaDistY;
	}
}

void	dda(t_map *map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (map->grid[ray->mapY][ray->mapX] == '1')
			hit = 1;
	}
}

void	wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void	get_wall_height(t_map *map, t_ray *ray, t_wall *wall)
{
	(void)map;
	wall->wall_height = (int)(HEIGHT / ray->perpWallDist);
	wall->draw_start = -wall->wall_height / 2 + HEIGHT / 2;
	wall->draw_end = wall->wall_height / 2 + HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
}
