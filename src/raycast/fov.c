/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 09:37:32 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/01 15:46:55 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_north_south_dir(t_map *map, char orientation)
{
	if (orientation == 'N')
	{
		map->player.dirY = -1;
		map->player.dirX = 0;
		map->player.planeY = 0;
		map->player.planeX = 0.66;
 	}
	else if (orientation == 'S')
	{
		map->player.dirY = 1;
		map->player.dirX = 0;
		map->player.planeY = 0;
		map->player.planeX = -0.66;
 	}
}

void	set_east_west_dir(t_map *map, char orientation)
{
	if (orientation == 'E')
	{
		map->player.dirY = 0;
		map->player.dirX = 1;
		map->player.planeY = 0.66;
		map->player.planeX = 0;
 	}
	else if (orientation == 'W')
	{
		map->player.dirY = 0;
		map->player.dirX = -1;
		map->player.planeY = -0.66;
		map->player.planeX = 0;
 	}
}

void	set_player_direction(t_map *map)
{	
	char	orientation;

	orientation = map->player.player_orientation;
	if(orientation == 'N' || orientation == 'S')
		set_north_south_dir(map, orientation);
	else if(orientation == 'E' || orientation == 'W')
		set_east_west_dir(map, orientation);
}

void	ray_direction(t_player *player, t_ray *ray, int x)
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	
	cameraX = (2.0 * x / WIDTH) - 1.0;
	ray->rayDirX = player->dirX + player->planeY * cameraX;
	ray->rayDirY = player->dirY + player->planeX * cameraX;
	ray->mapX = (int)player->posX;
	ray->mapY = (int)player->posY;
	ray->deltaDistY = fabs(1 / rayDirY);
	ray->deltaDistX = fabs(1 / rayDirX);
}

void	calculate_step_and_side_distance(t_map *map, t_ray *ray)
{
	// calcular step e sideDistance inicial 
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (map->player.posX - ray->mapX) * ray->deltaDistX; //distancia desde jogador ate proxima gridline (primeiro impacto com vertical grid line)
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - map->player.posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepX = -1;
		ray->deltaDistY = (map->player.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - map->player.posY) * ray->deltaDistY;
	}
}

void	DDA(t_map *map, t_ray *ray)
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

void	render_frame(t_map *map)
{
	double	DirX;
	double	DirY;
	int		x;
	
	x = 0;
	while (x < WIDTH)
	{
		ray_direction(&map->player, &map->ray, x);
		calculate_step_and_side_distance(map, &map->ray);
		DDA(map, &map->ray);
		x++;
	}
}

