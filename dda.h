/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/24 12:35:11 by valeriia         ###   ########.fr       */
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
#define PLAYER_SIZE 10
#define CELL_SIZE 30
#define EAST 'E'
#define WEST 'W'
#define SOUTH 'S'
#define NORTH 'N'

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

#define WIDTH 750
#define HEIGHT 750

#define MAP_WIDTH 25
#define MAP_HEIGHT 25

typedef struct	s_image {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct	s_fvector {
	double	x;
	double	y;
}	t_fvector;

typedef struct s_point
{
	double	x;
	double	y;
} t_point;

typedef struct s_coordinates
{
	int	x;
	int	y;
} t_coordinates;

typedef struct s_texture
{
	t_image	image;
	char	*name;
	int		width;
	int		height;
}	t_texture;


typedef struct	s_player {
	t_fvector	position;
	t_fvector	direction;
	t_fvector	plane;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_image		img;
	long		time;
	t_texture	*texture;
	int			**map;
	double		normilized_x[WIDTH];
} t_data;

void	draw_line(t_data *data, t_fvector a, t_fvector b, t_colors color, int second_window);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	clear_display(t_data *data);
void	dda(t_data *data);
void	put_image(t_data *data, t_texture *texture, int x, int y);

bool	is_direction(int coordinate);


#endif