/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:28 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/02 15:33:51 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	clear_player_image(t_map *map, int size)
{
	draw_square(&map->data.img, map->player.posX * size, map->player.posY * size, size, 0x000000);
} */

void init_game(t_map *map)
{
	map->data.mlx = mlx_init(); // criar funcao para iniciar janela/jogo
	map->data.mlx_win = mlx_new_window(map->data.mlx, WIDTH, HEIGHT, "cub3D");
	map->data.img.mlx_img = mlx_new_image(map->data.mlx, WIDTH, HEIGHT);
	map->data.img.addr = mlx_get_data_addr(map->data.img.mlx_img, &map->data.img.bpp, &map->data.img.line_len, &map->data.img.endian);
}

/* int	size_scales(int size)
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
} */
/* 
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
} */
/* 
void	expanded_minimap(t_map *map, int size)
{
//	render_minimap(map, size, 0x000000); //Clear small minimap
	render_minimap(map, (size * 2), 0x0000FF);
	draw_square(&map->data.img, map->player.posX * (size * 2), map->player.posY * (size * 2), (size * 2), 0x008000);
}

void	clear_expanded(t_map *map, int size)
{
	render_minimap(map, (size * 2), 0x000000);
	draw_square(&map->data.img, map->player.posX * (size * 2), map->player.posY * (size * 2), (size * 2), 0x000000);
} */

int	rendering_loop(t_map *map)
{
	/* int	size;

	size = (check_dims(map) / ((WIDTH / 1000.0) * 2));
//	if (!map->is_expanded || map->is_expanded % 2 == 0)
//	{
	clear_expanded(map, size);
	clear_player_image(map, size);
	render_minimap(map, size, 0x0000FF);
	player_movement(map);
	draw_square(&map->data.img, map->player.posX * size, map->player.posY * size, size, 0x008000);
//	}
if (map->is_expanded && map->is_expanded % 2 != 0)
{
	render_minimap(map, size, 0x000000);
	draw_square(&map->data.img, map->player.posX * size, map->player.posY * size, size, 0x000000);
	expanded_minimap(map, size);
	} */
	player_movement(map);
	render_world(map);
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
