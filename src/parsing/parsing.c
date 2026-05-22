/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:03:15 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/12 12:41:50 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//mapa so pode conter 6 carateres: 1,0,N,S,E,W
//tem de estar rodeado por paredes (1);
//separar config do mapa
//messagem de erro: "Error\n" seguida de mensagem informativa do erro
//parsing das texturas: verificar se o ficheiro existe, se pode ser aberto, se termina em .xpm (extensao)


void	check_identifier(char *line, t_map *map)
{
	while (is_space(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		check_duplicated(map, map->NO_identifier++);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		check_duplicated(map, map->SO_identifier++);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		check_duplicated(map, map->WE_identifier++);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		check_duplicated(map, map->EA_identifier++);
	else if (ft_strncmp(line, "F ", 2) == 0)
		check_duplicated(map, map->F_identifier++);
	else if (ft_strncmp(line, "C ", 2) == 0)
		check_duplicated(map, map->C_identifier++);
	else if (map->type_identifiers < 6)
		error_free_exit(MISCONFIGURATION, map);
}

char	*check_path_texture(char *line, t_map *map)
{
	char	*path;

	while (!is_space(*line))
		line++;
	path = ft_strtrim(line, " \n\t"); // trim do espacos tabs e newline
	if (!check_fd(path))
	{
		free(path);
		free_struct(map);
		exit(1);
	}
	check_file_extension_xpm(path, map);
	return (path);
}

int	check_if_valid_number(char *line)
{
	int	i;
	char	*value;

	value = ft_strtrim(line, " ");
	i = 0;
	while (value[i])
	{	
		if (value[i] == '-' || value[i] == '+')
			i++;
		if (!ft_isdigit(value[i]))
		{
			free(value);
			return (0);
		}
		i++;
	}
	free(value);
	return (1);
}

void	check_rgb_values(char *line, int rgb[3], t_map *map)
{
	char	**split;
	int		i;

	while (!is_space(*line))
		line++;
	line = ft_strtrim(line, " \n\t"); // trim do espacos tabs e newline
	split = ft_split(line, ',');
	free(line);
	i = 0;
	while (split[i])
	{
		if (!check_if_valid_number(split[i]))
			error_free_array_and_struct(RGB_ONLY_NUMBERS, map, split);
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			error_free_array_and_struct(RGB_RANGE_VALUES, map, split);
		i++;
	}
	if (i != 3)
		error_free_array_and_struct(MISSING_RGB_VALUES, map, split);
	free_array(split);
}

void	parsing_config(char *line, t_map *map)
{
	char	*path;

	while (is_space(*line))
		line++;
	check_identifier(line, map);
	if (*line == 'F')
		check_rgb_values(line, map->floor_rgb, map);
	else if (*line == 'C')
		check_rgb_values(line, map->ceiling_rgb, map);
	else
	{
		path = check_path_texture(line, map);
		if (line[0] == 'N')
			map->textures.NO = path;
		else if (line[0] == 'S')
			map->textures.SO = path;
		else if (line[0]== 'W')
			map->textures.WE = path;
		else if (line[0] == 'E')
			map->textures.EA = path;
	}
}


void	parsing(t_map *map)
{
	int	i;
	
	i = 0;
	while(map->map_array[i])
	{
		if (is_empty_line(map->map_array[i]))
		{
			i++;
			continue;
		}
			if (map->type_identifiers < 6)
				parsing_config(map->map_array[i], map);
			else
			{
				i = parsing_map_grid(map, i);
				break;
			}
		i++;
	}
	if (!map->is_map)
		error_free_exit(EMPTY_MAP, map);
}
