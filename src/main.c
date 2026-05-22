/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:28 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/22 18:13:50 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rendering_loop(t_map *map)
{
	int	size;
	t_map *tmp = map;

	size = 13;
	//player_movement(map);
	printf("ENTROU\n");
	printf("mapa 1: %p\n", tmp);
	printf("mapa 2: %s\n", tmp->grid[0]);
	render_minimap(map);
	draw_square(&map->data.img, map->player.posX * TILE, map->player.posY * TILE, size, 0x008000);
	mlx_put_image_to_window(map->data.mlx, map->data.mlx_win, map->data.img.mlx_img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	char	*file_name;
	t_map	*map;
	if (ac != 2)
	{
		printf("Invalid arguments\n");
		exit (1);
	}
	file_name = av[1];
	check_args(file_name);
	map = ft_calloc(1, sizeof(t_map)); //dar free struct e suas variaveis
	if (!map)
		return (1);
	map_load(file_name, map);
	parsing(map);
	set_player_direction(map);
	/* printf("posY: %f\n", map->player.posY);
	printf("posX: %f\n", map->player.posX);
	printf("dirY: %f\n", map->player.dirY);
	printf("dirX:%f\n", map->player.dirX); */
	map->data.mlx = mlx_init(); // criar funcao para iniciar janela/jogo
	map->data.mlx_win = mlx_new_window(map->data.mlx, WIDTH, HEIGHT, "cub3D");
	map->data.img.mlx_img = mlx_new_image(map->data.mlx, WIDTH, HEIGHT);
	map->data.img.addr = mlx_get_data_addr(map->data.img.mlx_img, &map->data.img.bpp, &map->data.img.line_len, &map->data.img.endian);
	mlx_put_image_to_window(map->data.mlx, map->data.mlx_win, map->data.img.mlx_img, 0, 0);
	rendering_loop(map);
	mlx_hook(map->data.mlx_win, 2, KeyPressMask, key_press, &map->player);
	mlx_hook(map->data.mlx_win, 3, KeyReleaseMask, key_release, &map->player);
	//rendering_loop(map);
//	mlx_loop_hook(map->data.mlx, rendering_loop, &map->data.img);
	mlx_loop(map->data.mlx);
	free_struct(map);
	return (0);
}
