/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/16 22:40:43 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

# include <sys/time.h>

# include "colors.h"
# include "events.h"
# include "../libft/libft.h"

# define PI 3.14159265358979323846
# define FOV 0.66
# define MOVE_SPEED 0.3
# define ROT_SPEED 0.3
# define PLAYER_SIZE 8
# define CELL_SIZE 35
# define MINI_TILE 15
# define MINIMAP_RADIUS 15
# define MINIMAP_OFFSET_X 35
# define MINIMAP_OFFSET_Y 25
# define WIDTH 1980
# define HEIGHT 1220

typedef enum e_characters
{
	EMPTY = '0',
	WALL = '1',
	SPACE = ' ',
	END = '\0',
	NEW_LINE = '\n',
	EAST = 'E',
	WEST = 'W',
	SOUTH = 'S',
	NORTH = 'N'
}	t_characters;

typedef enum e_move
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
}	t_move;

typedef enum e_direction
{
	N,
	E,
	S,
	W,
}	t_direction;

typedef enum e_side
{
	VERTICAL,
	HORIZONTAL,
}	t_side;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_fvector
{
	double	x;
	double	y;
}	t_fvector;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_coordinates
{
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_player_side
{
	t_point	up;
	t_point	down;
}	t_player_side;

typedef struct s_texture
{
	t_image	image;
	char	*name;
	int		width;
	int		height;
}	t_texture;

typedef struct s_player
{
	t_fvector		position;
	t_fvector		direction;
	t_fvector		plane;
	t_player_side	right_side;
	t_player_side	left_side;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_image		img;
	long		time;
	t_texture	*texture;
	char		**lekkereclrs;
	char		**script;
	char		**map;
	char		*e_t;
	char		*w_t;
	char		*s_t;
	char		*n_t;
	int			f;
	int			c;
	int			map_width;
	int			map_height;
	double		normalized_x[WIDTH];
}	t_data;

typedef struct s_dda_parameters
{
	t_point			player_position_in_cell;
	double			distance_to_wall;
	t_coordinates	player_cell;
	t_fvector		ray;
	t_fvector		initial_step;
	t_fvector		fixed_step;
	t_coordinates 	step;
	t_side			side;
	int				start_pixel;
	int				end_pixel;
	int				x;
}	t_dda_parameters;

typedef struct s_flash_params
{
	t_fvector	player_pos;
	int			map_start_x;
	int			map_start_y;
	double		fov;
	int			rays;
	double		step_angle;
	double		start;
}	t_flash_params;

void	dda(t_data *data);
bool	is_direction(int coordinate);

//DRAW UTILS
void	draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

//MATH
void	rotate(t_fvector *dir, t_fvector temp, double radian);
void	swap_points(t_fvector *a, t_fvector *b);

//MINIMAP
void	draw_player(t_data *data);
void	draw_map_fill(t_data *data);
void	draw_map_border(t_data *data);
void	init_player(t_data *data);

//EVENT
void	init_hooks(t_data *data);
int		close_event(t_data *data);

//GENERAL
int		display(t_data *data);
void	draw_flashlight(t_data *data);

//MOVEMENT
int		move_player(int keycode, t_data *data);

// VALIDATION OF INPUT
int		valid_input(char *name);

// READ MAP
char	**read_map(char *map_script);
void	free_double_arr(char **map);

//MINIMAP UTILS
double	convert_to_minimap_coordinates(double position);
void	fill_square(t_data *data, int px, int py, t_colors color);
void	border_square(t_data *data, int px, int py);

// VALID MAP
bool	map_valid(t_data	*data);

// SCRIPT
bool	is_map_line(char *line);
void	replace_null_terminated_strings(t_data *data, char **strings);
bool	is_script_valid(t_data *data);

//FREE
void	free_mlx_data(void *mlx, void *img, void *mlx_win);
void	free_textures(t_data *data);

//COLOR
t_colors find_color(t_data *data, char *input_clr);


//DDA
double	find_distance_to_wall( t_data *data, t_dda_parameters *dda_parameters, t_coordinates player_cell);
void	get_initial_step(t_dda_parameters *params);
void	get_fixed_step_between_lines(t_fvector ray, t_fvector *fixed_step);
void	get_direction_step(t_dda_parameters *dda_parameters);
void	get_x_ray_coordinates(int x, t_data *data, t_fvector *ray);
void	get_player_cell(t_point player_position_in_cell, t_coordinates *player_cell);
void	get_player_position_on_map(t_data *data,t_point *player_position_in_cell);
void	draw_floor(t_data *data, int end_pixel, t_colors color, int x);
void	draw_celing(t_data *data,int start_pixel,t_colors color,int x);
void	get_wall_start_and_end(int line_height, int *start_pixel, int *end_pixel);

//WALL COLISION
bool	is_colliding_with_wall(t_player player, char **map, double shift_x, double shift_y);

#endif