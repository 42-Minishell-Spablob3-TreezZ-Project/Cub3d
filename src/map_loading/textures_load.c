/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:24:18 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/25 13:45:03 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_tex(t_map *map, t_tex *tex, char *path)
{
	printf("Loading texture: %s\n", path);
	tex->img = mlx_xpm_file_to_image(map->data.mlx, path, \
&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("failed to load texture");
		return ;
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, \
&tex->size_line, &tex->endian);
	if (!tex->data)
		return ;
}

void	load_textures(t_map *map)
{
	load_tex(map, &map->north_tex, map->textures.no);
	load_tex(map, &map->south_tex, map->textures.so);
	load_tex(map, &map->west_tex, map->textures.we);
	load_tex(map, &map->east_tex, map->textures.ea);
}
