/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:55 by joapedro          #+#    #+#             */
/*   Updated: 2026/07/14 16:51:56 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//verificar se diretorio
//abrir o fd do mapa;
//verificar extensao do ficheiro: ".cub";
//verificar se o ficheiro tem permissoes

void	max_is_directory(char *file_name, t_map *map)
{
	if (open(file_name, O_DIRECTORY) == -1)
		return ;
	else
	{
		free(file_name);
		error_free_exit(DIRECTORY, map);
	}
}

void	is_directory(char *file_name)
{
	if (open(file_name, O_DIRECTORY) == -1)
		return ;
	else
		error_exit(DIRECTORY);
}

int	check_fd(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nNo such file or directory: '%s'\n", str);
		return (0);
	}
	close(fd);
	return (1);
}

void	check_file_extension(char *str)
{
	char	*file_extension;
	int		len;

	file_extension = ft_strrchr(str, '/');
	file_extension = ft_strrchr(str, '.');
	if (!file_extension)
		error_exit(MISSING_EXTENSION);
	len = ft_strlen(file_extension);
	if ((ft_strncmp(file_extension, ".cub", 4) != 0) || len != 4)
		error_exit(WRONG_EXTENSION);
}

void	check_args(char *file_name)
{
	is_directory(file_name);
	if (!check_fd(file_name))
		exit(1);
	check_file_extension(file_name);
}
