/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/25 20:25:41 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		my_mlx_pixel_put(&(data->img), ((data->player.position.x) * CELL_SIZE  - PLAYER_SIZE / 2 + x) + WIDTH - 1, ((data->player.position.y) * CELL_SIZE  - PLAYER_SIZE / 2 + y), GREEN);
		while (x < PLAYER_SIZE)
		{
			my_mlx_pixel_put(&(data->img), ((data->player.position.x) * CELL_SIZE  - PLAYER_SIZE / 2 + x) + WIDTH - 1, ((data->player.position.y) * CELL_SIZE  - PLAYER_SIZE / 2 + y), GREEN);
			x++;
		}
		y++;
	}
}

void	fill_square(t_data *data, int px, int py, t_colors color)
{
	int	x;
	int	y;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
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
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			if ((y == 0 || y == CELL_SIZE - 1)
			|| (x == 0 || x == CELL_SIZE - 1))
			{
				my_mlx_pixel_put(&(data->img), x + px, y + py, PURPLE);
			}
			x++;
		}
		y++;
	}
}

void	draw_map_fill(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MAP_HEIGHT)
	{
		px = 0;
		while (px < MAP_WIDTH)
		{
			if (data->map[py][px] >= 1 && !is_direction(data->map[py][px]))
			{
				fill_square(data, px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE, YELLOW);
				border_square(data,  px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE);
			}
			px++;
		}
		py++;
	}
}

void	draw_map_border(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MAP_HEIGHT)
	{
		px = 0;
		while (px < MAP_WIDTH)
		{
			if (data->map[py][px] >= 1 && !is_direction(data->map[py][px]))
			{
				fill_square(data, px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE, YELLOW);
			}
			border_square(data,  px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE);
			px++;
		}
		py++;
	}
}


