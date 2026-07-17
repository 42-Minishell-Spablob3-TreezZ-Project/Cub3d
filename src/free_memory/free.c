/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:23:52 by grui-ant          #+#    #+#             */
/*   Updated: 2026/07/14 12:13:58 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_text_path(t_texture *t)
{
	if (t->no)
		free(t->no);
	if (t->so)
		free(t->so);
	if (t->we)
		free(t->we);
	if (t->ea)
		free(t->ea);
}

void	free_struct(t_map *map)
{
	if (!map)
		return ;
	if (map->map_array)
		free_array(map->map_array);
	if (map->grid)
		free_array(map->grid);
	free_text_path(&map->textures);
	free(map);
}

void	destroy_textures_img(t_map *map)
{
	if (map->north_tex.img)
		mlx_destroy_image(map->data.mlx, map->north_tex.img);
	if (map->south_tex.img)
		mlx_destroy_image(map->data.mlx, map->south_tex.img);
	if (map->west_tex.img)
		mlx_destroy_image(map->data.mlx, map->west_tex.img);
	if (map->east_tex.img)
		mlx_destroy_image(map->data.mlx, map->east_tex.img);
	mlx_destroy_image(map->data.mlx, map->data.img.mlx_img);
}

void	close_win(t_map *map)
{
	destroy_textures_img(map);
	mlx_destroy_window(map->data.mlx, map->data.mlx_win);
	mlx_destroy_display(map->data.mlx);
	free(map->data.mlx);
	free_struct(map);
	exit(0);
}
