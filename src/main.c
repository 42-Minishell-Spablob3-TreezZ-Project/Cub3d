/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:28 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/30 14:24:46 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_player_image(t_map *map, int size)
{
	draw_square(&map->data.img, map->player.pos_x * size, map->player.pos_y * size, size, 0x000000);
}

void	init_game(t_map *map)
{
	map->data.mlx = mlx_init(); // criar funcao para iniciar janela/jogo
	map->data.mlx_win = mlx_new_window(map->data.mlx, WIDTH, HEIGHT, "cub3D");
	map->data.img.mlx_img = mlx_new_image(map->data.mlx, WIDTH, HEIGHT);
	map->data.img.addr = mlx_get_data_addr(map->data.img.mlx_img, &map->data.img.bpp, &map->data.img.line_len, &map->data.img.endian);
}

int	rendering_loop(t_map *map)
{
	int	size;

	size = (check_dims(map) / ((WIDTH / 1000.0) * 2));
//	if (!map->is_expanded || map->is_expanded % 2 == 0)
//	{
	clear_expanded(map, size);
	clear_player_image(map, size);
	render_minimap(map, size, 0x0000FF);
	player_movement(map);
	draw_square(&map->data.img, map->player.pos_x * size, map->player.pos_y * size, size, 0x008000);
//	}
	render_world(map);
	if (map->is_expanded && map->is_expanded % 2 != 0)
	{
	render_minimap(map, size, 0x000000);
	draw_square(&map->data.img, map->player.pos_x * size, map->player.pos_y * size, size, 0x000000);
	expanded_minimap(map, size);
	}
	player_movement(map);
	//render_world(map);
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
	init_game(map);
	load_textures(map);
	mlx_hook(map->data.mlx_win, 2, KeyPressMask, key_press, map);
	mlx_hook(map->data.mlx_win, 3, KeyReleaseMask, key_release, map);
	mlx_hook(map->data.mlx_win, 17, 0, &close_win, map);
	mlx_loop_hook(map->data.mlx, rendering_loop, map);
	mlx_loop(map->data.mlx);
	free_struct(map);
	return (0);
}
