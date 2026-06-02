/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:54:40 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/02 12:29:20 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_direction(t_player *player, t_ray *ray, int x)
{
	double	cameraX;
	
	cameraX = (2.0 * x / WIDTH) - 1.0;
	ray->rayDirX = player->dirX + player->planeX * cameraX;
	ray->rayDirY = player->dirY + player->planeY * cameraX;
	ray->mapX = (int)player->posX;
	ray->mapY = (int)player->posY;
	ray->deltaDistY = fabs(1 / ray->rayDirY); // distancia que o raio precisa percorrer para atravessar celula da grelha X ou Y
	ray->deltaDistX = fabs(1 / ray->rayDirX);
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

void	perpWallDist(t_ray *ray)
{
	// calcular a distancia da camara ate parede evitando o efeito fisheye
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void	draw_wall(t_map *map, t_ray *ray, t_wall *wall)
{
	wall->wall_height = (int)(HEIGHT / ray->perpWallDist); //tamanho da wall inversamente proporcional a distancia entre player e wall.
	wall->draw_start = wall->wall_height / 2 + HEIGHT / 2;
	if (wall->draw_end < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->wall_height / 2 + HEIGHT / 2;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
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
		dda(map, &map->ray);
		wall_distance(&map->ray);
		draw_wall(map, &map->ray, &map->wall);
		x++;
	}
}