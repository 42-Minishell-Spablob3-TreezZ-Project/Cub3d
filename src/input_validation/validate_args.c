/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:25:55 by joapedro          #+#    #+#             */
/*   Updated: 2026/05/07 14:55:57 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//verificar se diretorio
//abrir o fd do mapa;
//verificar extensao do ficheiro: ".cub";
//verificar se o ficheiro tem permissoes

void	is_directory(char *file_name)
{
	struct stat	sb;

	if (stat(file_name, &sb) == -1)
		return ;
	if (S_ISDIR(sb.st_mode))
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
