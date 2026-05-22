/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 10:58:00 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/12 15:20:42 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

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
