/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/09 17:32:10 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdbool.h>

#include <sys/time.h>

#include "colors.h"
#include "events.h"

#define PI 3.14159265358979323846
#define PLAYER_SIZE 15
#define POINTER_SIZE 20
#define CELL_SIZE 30
#define CELLS_COUNT 20
#define EAST 'E'
#define WEST 'W'
#define SOUTH 'S'
#define NORTH 'N'

#define WIDTH 720
#define HEIGHT 720

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

typedef struct	s_image {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct	s_fvector {
	float	x;
	float	y;
}	t_fvector;

typedef struct s_point
{
	int	x;
	int	y;
} t_point;

typedef struct	s_player {
	t_fvector	position;
	t_fvector	direction;
	t_fvector	center;
	float		rotation_angle;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_image		img;
	long		time;
	int			**map;
} t_data;

int	check_wall(t_data *data, double px, double py);
void	draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color, int second_window);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	clear_display(t_data *data);
void	dda(t_data *data);


bool is_direction(int coordinate);
int	get_cell_on_grid(int **map, double px, double py);


#endif