/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:23:52 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/25 13:44:28 by grui-ant         ###   ########.fr       */
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

void	free_textures(t_texture *t)
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
	free_textures(&map->textures);
	free(map);
}

int	close_win(t_map *map)
{
	mlx_destroy_window(map->data.mlx, map->data.mlx_win);
	mlx_destroy_display(map->data.mlx);
	free_struct(map);
	exit (0);
}
