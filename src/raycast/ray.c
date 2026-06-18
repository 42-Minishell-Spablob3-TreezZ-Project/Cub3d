/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 09:54:40 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/02 17:57:28 by joapedro         ###   ########.fr       */
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
	ray->deltaDistY = fabs(1 / ray->rayDirY); //distancia que o raio precisa percorrer para atravessar celula da grelha X ou Y
	ray->deltaDistX = fabs(1 / ray->rayDirX);
}

void	 calculate_step_and_side_distance(t_map *map, t_ray *ray)
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

void	wall_distance(t_ray *ray)
{
	// calcular a distancia da camara ate parede evitando o efeito fisheye
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	
}

void	get_wall_height(t_map *map, t_ray *ray, t_wall *wall)
{
	(void)map;
	wall->wall_height = (int)(HEIGHT / ray->perpWallDist); //tamanho da wall inversamente proporcional a distancia entre player e wall.
	
	wall->draw_start = -wall->wall_height / 2 + HEIGHT / 2;
	wall->draw_end = wall->wall_height / 2 + HEIGHT / 2;
	
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
}

int rgb_to_int(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

void	render_ceiling_floor(t_map *map, int x, t_wall *wall)
{
	int	y;

	y = 0;
	while (y < wall->draw_start)
	{
		img_pix_put(&map->data.img, x, y, rgb_to_int(map->ceiling_rgb[0],
			map->ceiling_rgb[1],
			map->ceiling_rgb[2]));
		y++;
	}
	y = wall->draw_end;
	while (y < HEIGHT)
	{
		img_pix_put(&map->data.img, x, y, rgb_to_int(map->floor_rgb[0],
			map->floor_rgb[1],
			map->floor_rgb[2]));
		y++;
	}
}
void	render_wall(t_map *map, int x)
{
	int	y;
	int	color;
	t_tex *tex;
	double wallX;
	int	texX;
	int	texY;
	double	step;

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
	//calculate_wall_hit_point
	if (map->ray.side == 0)
		wallX = map->player.posY + map->ray.perpWallDist * map->ray.rayDirY;
	else
		wallX = map->player.posX + map->ray.perpWallDist * map->ray.rayDirX;
	wallX -= floor(wallX);
	texX = (int)(wallX * tex->width);
	//flip the texture
	if (map->ray.side == 0 && map->ray.rayDirX > 0)
		texX = tex->width - texX - 1;
	if (map->ray.side == 1 && map->ray.rayDirY < 0)
		texX = tex->width - texX - 1;
	// start drawing
	step = (double)tex->height / map->wall.wall_height;
	double texPos = (map->wall.draw_start - HEIGHT / 2 + map->wall.wall_height / 2) * step;
	y = map->wall.draw_start;
	while (y < map->wall.draw_end)
	{
		texY = (int)texPos;
		texPos += step;
		char * pixel = tex->data + (texY * tex->size_line + texX * (tex->bpp / 8));
		color = *(unsigned int *)pixel;
		// darken the sides of the wall
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
