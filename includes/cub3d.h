#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1920
# define HEIGHT 1080
# define SPEED 0.02
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
# define ROTATE_SPEED 0.01

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
	double	deltaDistY;
	double	deltaDistX;
	double	rayDirX;
	double	rayDirY;
	int		mapX; // posicao da celula em que estamos
	int		mapY;
	double	sideDistX; // comprimento do raio desde a posicao do player ate proxima x or y-side
	double	sideDistY;
	int		side;
	int		stepX;
	int		stepY;
	double	perpWallDist;
}	t_ray;

typedef struct	s_wall
{
	int	wall_height;
	int	draw_start;
	int	draw_end;

}	t_wall;

typedef struct	s_player
{
	char	player_orientation;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeY;
	double	planeX;
	double	player_angle;
	int		up;
	int		down;
	int		left;
	int		right;
	int		rot_left;
	int		rot_right;
}	t_player;

typedef struct	s_tex
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_tex;

typedef struct	s_texture
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;

}	t_texture;

typedef struct	s_map
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
	int			NO_identifier;
	int			SO_identifier;
	int			WE_identifier;
	int			EA_identifier;
	int			F_identifier;
	int			C_identifier;
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
//void	edge_scan(t_map *map);

//free memory
void	free_struct(t_map *map);
void	free_array(char **array);
int		close_win(t_map *map);

// error
void	error_exit(char *message);
void	error_free_exit(char *message, t_map *map);
void	error_free_array_and_struct(char *message, t_map *map, char **array);


//minimap
void	render_minimap(t_map *map, int size, int color);
void	draw_square(t_img *img, int x, int y, int size, int color);
int		rendering_loop(t_map *map);

//expanded minimap
int		size_scales(int size);
int		check_dims(t_map *map);
void	expanded_minimap(t_map *map, int size);
void	clear_expanded(t_map *map, int size);

//raycasting
void	set_player_direction(t_map *map);

//Movement
int		key_press(int key, t_map *map);
int		key_release(int key, t_map *map);
void	player_movement(t_map *map);
//void	clear_player_image(t_map *map, int size);

//render world
void	render_world(t_map *map);
void	img_pix_put(t_img *img, int x, int y, int color);
void	load_textures(t_map *map);
int		rgb_to_int(int r, int g, int b);

#endif
