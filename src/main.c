/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:28 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/28 16:37:09 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	clear_player_image(t_map *map, int size)
{
	draw_square(&map->data.img, map->player.posX * size, map->player.posY * size, size, 0x000000);
}
void init_game(t_map *map)
{
	map->data.mlx = mlx_init(); // criar funcao para iniciar janela/jogo
	map->data.mlx_win = mlx_new_window(map->data.mlx, WIDTH, HEIGHT, "cub3D");
	map->data.img.mlx_img = mlx_new_image(map->data.mlx, WIDTH, HEIGHT);
	map->data.img.addr = mlx_get_data_addr(map->data.img.mlx_img, &map->data.img.bpp, &map->data.img.line_len, &map->data.img.endian);
}

int	size_scales(int size)
{
	if (size < 25)
		return (75);
	if (size >= 25 && size < 50)
		return (35);
	if (size >= 50 && size < 75)
		return (28);
	if (size >= 75 && size < 100)
		return (20);
	if (size >= 100)
		return (10);
	return (0);
}

int	check_dims(t_map *map)
{
	int	x;
	int	y;
	int	size;

	size = 0;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
			x++;
		if (x > size)
			size = x;
		y++;
	}
	if (y > x)
		size = y;
	size = size_scales(size);
	return (size);
}

int	rendering_loop(t_map *map)
{
	int	size;

	size = (check_dims(map) / ((WIDTH / 1000.0) * 2));
	clear_player_image(map, size);
	render_minimap(map, size);
	player_movement(map);
	draw_square(&map->data.img, map->player.posX * size, map->player.posY * size, size, 0x008000);
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
	mlx_hook(map->data.mlx_win, 2, KeyPressMask, key_press, map);
	mlx_hook(map->data.mlx_win, 3, KeyReleaseMask, key_release, map);
	mlx_loop_hook(map->data.mlx, rendering_loop, map);
	mlx_loop(map->data.mlx);
	free_struct(map);
	return (0);
}
