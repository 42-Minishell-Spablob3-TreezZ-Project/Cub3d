/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:24:18 by grui-ant          #+#    #+#             */
/*   Updated: 2026/07/14 18:46:23 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_tex(t_map *map, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(map->data.mlx, path, \
&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Warning: failed to load texture\n");
		return (1);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, \
&tex->size_line, &tex->endian);
	if (!tex->data)
		return (1);
	return (0);
}

void	load_textures(t_map *map)
{
	if ((load_tex(map, &map->north_tex, map->textures.no) == 1) \
|| (load_tex(map, &map->south_tex, map->textures.so) == 1) \
|| (load_tex(map, &map->west_tex, map->textures.we) == 1) \
|| (load_tex(map, &map->east_tex, map->textures.ea) == 1))
	{
		close_win(map);
		return ;
	}
}
