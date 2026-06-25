/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 10:58:00 by joapedro          #+#    #+#             */
/*   Updated: 2026/06/25 13:46:27 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_empty_line(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

void	check_duplicated(t_map *map, int identifier)
{
	if (identifier > 0)
		error_free_exit(DUPLICATED, map);
	map->type_identifiers++;
}

void	check_file_extension_xpm(char *path, t_map *map)
{
	char	*file_extension;
	int		len;

	file_extension = ft_strrchr(path, '/');
	file_extension++;
	file_extension = ft_strchr(file_extension, '.');
	if (!file_extension)
	{
		free(path);
		error_free_exit(MISSING_EXTENSION_XPM, map);
	}
	len = ft_strlen(file_extension);
	if ((ft_strncmp(file_extension, ".xpm", 4) != 0) && len == 4)
	{
		free(path);
		error_free_exit(WRONG_EXTENSION, map);
	}
}

void	check_identifier(char *line, t_map *map)
{
	while (is_space(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		check_duplicated(map, map->no_identifier++);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		check_duplicated(map, map->so_identifier++);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		check_duplicated(map, map->we_identifier++);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		check_duplicated(map, map->ea_identifier++);
	else if (ft_strncmp(line, "F ", 2) == 0)
		check_duplicated(map, map->f_identifier++);
	else if (ft_strncmp(line, "C ", 2) == 0)
		check_duplicated(map, map->c_identifier++);
	else if (map->type_identifiers < 6)
		error_free_exit(MISCONFIGURATION, map);
}
