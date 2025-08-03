/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/03 09:42:51 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

bool	is_direction(int coordinate)
{
	return (coordinate == NORTH
		|| coordinate == EAST
		|| coordinate == SOUTH
		|| coordinate == WEST);
}

bool	is_sprite(int coordinate)
{
	return (coordinate == SPRITE);
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

	y = 0;
	px *= MINI_TILE;
	py *= MINI_TILE;
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
