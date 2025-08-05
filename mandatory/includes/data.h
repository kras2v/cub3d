/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:55:52 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/05 13:21:09 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <X11/keysym.h>
# include <mlx.h>
# include <sys/time.h>
# include <limits.h>
# include <math.h>

# include "player.h"
# include "libft.h"
# include "sprite.h"
# include "dda.h"
# include "errors.h"
# include "events.h"
# include "map.h"

typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	t_player			player;
	t_image				img;
	long				time;
	t_texture_params	*texture_params;
	t_sprite			*sprite;
	char				**script;
	char				**map;
	char				**texture_names;
	char				*door;
	int					f;
	int					c;
	int					map_width;
	int					map_height;
	time_t				door_last_open;
	t_coordinates		door_coordinates;
	double				normalized_x[WIDTH];
	double				z_buffer[WIDTH];
}	t_data;

//BRESENHAM
void		increase_stepping(int *p, int dir,
				t_coordinates *coords, t_coordinates delta);
void		swap_axis(t_fvector *a);
void		get_direction(int *dir, int *delta);
void		assign_delta_coords(t_coordinates *delta,
				t_fvector *a, t_fvector *b);

int			display(t_data *data);
void		start_mlx(t_data *data);

int			initialize_data(t_data *data);
bool		validate_user_input(t_data *data, int argc, char **args);

void		close_on_error(t_data *data, char *err_msg);
bool		is_file_name_valid(t_data *data, char *name);

void		dda(t_data *data);
bool		is_direction(int coordinate);

//DRAW UTILS
void		draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color);
void		my_mlx_pixel_put(t_image *data, int x, int y, int color);

//MINIMAP
void		draw_player(t_data *data);
void		draw_map_fill(t_data *data);
void		draw_map_border(t_data *data);
void		init_player(t_data *data);

//EVENT
void		init_hooks(t_data *data);
int			close_event(t_data *data);

//GENERAL
int			display(t_data *data);
void		draw_flashlight(t_data *data);

//MOVEMENT
int			move_player(int keycode, t_data *data);

// READ MAP
char		**read_map(t_data *data, char *map_script);
void		free_double_arr(char **map);
void		free_until_end(char **strings, int y);

//MINIMAP UTILS
double		convert_to_minimap_coordinates(double position);
void		fill_square(t_data *data, int px, int py, t_colors color);
void		border_square(t_data *data, int px, int py);

// VALID MAP
bool		check_map_walls(t_data *data);
bool		is_map_valid(t_data	*data);
bool		invalid_char(t_data *data);
bool		char_counter(t_data *data);

// SCRIPT
bool		is_map_line(char *line);
int			replace_null_terminated_strings(t_data *data, char **strings);
bool		is_script_valid(t_data *data);

//FREE
void		free_mlx_data(void *mlx, void *img, void *mlx_win);
void		free_textures(t_data *data);
void		free_sprite(t_data *data);

//COLOR
t_colors	find_color(t_data *data, char *input_clr);

//
int			get_minimum_tile(double position);

//DDA
double		find_distance_to_wall( t_data *data,
				t_dda_parameters *dda_parameters, t_coordinates player_cell);
void		get_initial_step(t_dda_parameters *params);
void		get_fixed_step_between_lines(t_fvector ray, t_fvector *fixed_step);
void		get_direction_step(t_dda_parameters *dda_parameters);
void		get_x_ray_coordinates(int x, t_data *data, t_fvector *ray);
void		get_player_cell(t_point player_position_in_cell,
				t_coordinates *player_cell);
void		get_player_position_on_map(t_data *data,
				t_point *player_position_in_cell);
void		draw_floor(t_data *data, int end_pixel, t_colors color, int x);
void		draw_celing(t_data *data, int start_pixel, t_colors color, int x);
void		get_wall_start_and_end(int line_height,
				int *start_pixel, int *end_pixel);

//WALL COLISION
bool		is_wall(int coordinate);
bool		is_colliding(t_player player, char **map,
				t_point shift, bool (*checker)(int));

#endif