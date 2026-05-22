#include "cub3d.h"

void	error_exit(char *message)
{
	printf("Error\n%s\n", message);
	exit(1);
}


void	error_free_exit(char *message, t_map* map)
{
	free_struct(map);
	error_exit(message);
}

void	error_free_array_and_struct(char *message, t_map *map, char **array)
{
	free_array(array);
	error_free_exit(message, map);
}