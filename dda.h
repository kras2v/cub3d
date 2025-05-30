/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:33:54 by kvalerii          #+#    #+#             */
/*   Updated: 2025/05/30 19:08:26 by valeriia         ###   ########.fr       */
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

#include "colors.h"
#include "events.h"

#define PI 3.14159265358979323846
#define PLAYER_SIZE 15
#define POINTER_SIZE 20
#define CELL_SIZE 30
#define CELLS_COUNT 20

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
	t_point		position;
	t_fvector	direction;
	t_fvector	plane;
	t_fvector	center;
	t_fvector	delta_position;
	float		rotation_angle;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_image		img;
	int			**map;
} t_data;


void	draw_line(t_data *data, t_point a, t_point b);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

#endif