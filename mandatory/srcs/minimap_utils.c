/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 14:06:15 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool	is_direction(int coordinate)
{
	return (coordinate == NORTH
		|| coordinate == EAST
		|| coordinate == SOUTH
		|| coordinate == WEST);
}

double	convert_to_minimap_coordinates(double position)
{
	return ((position - ((int)position - MINIMAP_RADIUS)) * MINI_TILE);
}

void	fill_square(t_data *data, int px, int py, t_colors color)
{
	int	x;
	int	y;

	y = 0;
	px *= MINI_TILE;
	py *= MINI_TILE;
	while (y < MINI_TILE)
	{
		x = 0;
		while (x < MINI_TILE)
		{
			my_mlx_pixel_put(&(data->img), x + px, y + py, color);
			x++;
		}
		y++;
	}
}

void	border_square(t_data *data, int px, int py)
{
	int	x;
	int	y;
	int	margin;

	y = 0;
	margin = 0;
	px *= MINI_TILE;
	py *= MINI_TILE;
	if (py / MINI_TILE == MINIMAP_OFFSET_Y - 1
		|| px / MINI_TILE == MINIMAP_OFFSET_X - 1)
		margin = -1;
	while (y < MINI_TILE)
	{
		x = 0;
		while (x < MINI_TILE)
		{
			if ((y == 0 || y == MINI_TILE - 1)
				|| (x == 0 || x == MINI_TILE - 1))
			{
				my_mlx_pixel_put(&(data->img), x + px, y + py, PURPLE);
			}
			x++;
		}
		y++;
	}
}
