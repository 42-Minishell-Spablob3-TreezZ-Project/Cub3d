/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:26:13 by grui-ant          #+#    #+#             */
/*   Updated: 2026/07/14 12:30:04 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1920
# define HEIGHT 1080
# define SPEED 0.05
# define TILE 32
# define PI 3.14159265358979323846
# include "../libft/libft.h"
# include "get_next_line.h"
# include "error_messages.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>

//Keys
# define W 119
# define A 97
# define S 115
# define D 100
# define M 109 //Expand and minimize minimap
# define ESC 65307 //Escape key to close game
# define LEFT 65361
# define RIGHT 65363
# define ROTATE_SPEED 0.04

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}	t_data;

typedef struct s_ray
{
	double	delta_dist_y;
	double	delta_dist_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x; // distance between player pos and closest x or y
	double	side_dist_y;
	int		side;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_wall
{
	int	wall_height;
	int	draw_start;
	int	draw_end;
}	t_wall;

typedef struct s_player
{
	char	player_orientation;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_y;
	double	plane_x;
	double	player_angle;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rot_left;
	int		rot_right;
}	t_player;

typedef struct s_tex
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_tex;

typedef struct s_walltex
{
	int		tex_x;
	double	tex_pos;
	double	step;
}	t_walltex;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

}	t_texture;

typedef struct s_specs
{
	int	size;
	int	color;
}	t_specs;

typedef struct s_map
{
	char		**map_array;
	char		**grid;
	int			width;
	int			height;
	int			is_expanded;
	t_player	player;
	t_data		data;
	t_ray		ray;
	t_wall		wall;
	t_texture	textures;
	t_tex		north_tex;
	t_tex		south_tex;
	t_tex		east_tex;
	t_tex		west_tex;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	int			is_map;
	int			player_count;
	int			no_identifier;
	int			so_identifier;
	int			we_identifier;
	int			ea_identifier;
	int			f_identifier;
	int			c_identifier;
	int			type_identifiers;
}	t_map;

// input validation
void	check_args(char *file_name);

// map loading
void	map_load(char *file_name, t_map *map);
void	fill_map_array(char *file_name, t_map *map);
int		check_fd(char *str);

// parsing
void	parsing(t_map *map);

// parsing utils
int		is_space(char c);
int		is_empty_line(char *str);
void	check_map_chars(char **map_grid, t_map *map);
void	check_duplicated(t_map *map, int identifier);
void	check_file_extension_xpm(char *path, t_map *map);
int		parsing_map_grid(t_map *map, int start);
int		is_player(char c, t_map *map);
int		get_longest_line(t_map *map);
void	set_map_dimensions(t_map *map);
void	flood_fill(char **grid, t_map *map, int y, int x);
void	check_identifier(char *line, t_map *map);

//free memory
void	free_struct(t_map *map);
void	free_array(char **array);
void	close_win(t_map *map);

// error
void	error_exit(char *message);
void	error_free_exit(char *message, t_map *map);
void	error_free_array_and_struct(char *message, t_map *map, char **array);

//minimap
void	render_minimap(t_map *map, t_specs specs);
void	draw_square(t_img *img, int x, int y, t_specs specs);
int		rendering_loop(t_map *map);
void	draw_player(t_img *img, int x, int y, t_specs specs);
int		obtain_x(t_map *map);
int		obtain_y(t_map *map);
void	render_bg(t_map *map, t_specs specs);
void	render_highlight_bg(t_map *map, t_specs specs);

//expanded minimap
int		size_scales(int size);
int		check_dims(t_map *map);
void	expanded_minimap(t_map *map, int size);
void	clear_expanded(t_map *map, int size);

//raycasting
void	set_player_direction(t_map *map);
void	ray_direction(t_player *player, t_ray *ray, int x);
void	calculate_step_and_side_distance(t_map *map, t_ray *ray);
void	dda(t_map *map, t_ray *ray);
void	wall_distance(t_ray *ray);
void	get_wall_height(t_map *map, t_ray *ray, t_wall *wall);
int		rgb_to_int(int r, int g, int b);
void	render_ceiling_floor(t_map *map, int x, t_wall *wall);
void	render_wall(t_map *map, int x);
void	render_world(t_map *map);

//Movement
int		key_press(int key, t_map *map);
int		key_release(int key, t_map *map);
void	player_movement(t_map *map);

//render world
void	render_world(t_map *map);
void	img_pix_put(t_img *img, int x, int y, int color);
void	load_textures(t_map *map);
int		rgb_to_int(int r, int g, int b);

#endif
