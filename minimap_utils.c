/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/26 19:04:18 by eklymova         ###   ########.fr       */
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
		// my_mlx_pixel_put(&(data->img), ((data->player.position.x) * MINIMAP_TILE  - PLAYER_SIZE / 2 + x) + WIDTH - 1, ((data->player.position.y) * MINIMAP_TILE  - PLAYER_SIZE / 2 + y), GREEN);
		while (x < PLAYER_SIZE)
		{
			my_mlx_pixel_put(&(data->img),
			(data->player.position.x * MINIMAP_TILE) - PLAYER_SIZE / 2 + x + MINIMAP_OFFSET_X,
			(data->player.position.y * MINIMAP_TILE) - PLAYER_SIZE / 2 + y + MINIMAP_OFFSET_Y,
			GREEN);
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
	while (y < MINIMAP_TILE)
	{
		x = 0;
		while (x < MINIMAP_TILE)
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
	while (y < MINIMAP_TILE)
	{
		x = 0;
		while (x < MINIMAP_TILE)
		{
			if ((y == 0 || y == MINIMAP_TILE + 1) || (x == 0 || x == MINIMAP_TILE + 1))
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
			if (data->map[py][px] == WALL && !is_direction(data->map[py][px]))
			{
				fill_square(data, px * MINIMAP_TILE + MINIMAP_OFFSET_X, py * MINIMAP_TILE + MINIMAP_OFFSET_Y, YELLOW);
				border_square(data, px * MINIMAP_TILE + MINIMAP_OFFSET_X, py * MINIMAP_TILE + MINIMAP_OFFSET_Y);
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
			if (data->map[py][px] == WALL && !is_direction(data->map[py][px]))
			{
				fill_square(data, px * MINIMAP_TILE + MINIMAP_OFFSET_X, py * MINIMAP_TILE + MINIMAP_OFFSET_Y, YELLOW);
			}
			border_square(data, px * MINIMAP_TILE + MINIMAP_OFFSET_X, py * MINIMAP_TILE + MINIMAP_OFFSET_Y);
			px++;
		}
		py++;
	}
}

void draw_map_partial(t_data *data)
{
	int px, py;

	for (py = 0; py < MAP_HEIGHT; py++)
	{
		for (px = 0; px < MAP_WIDTH; px++)
		{
			int screen_x = MINIMAP_OFFSET_X + px * MINIMAP_TILE;
			int screen_y = MINIMAP_OFFSET_Y + py * MINIMAP_TILE;

			if (data->map[py][px] == WALL)
				fill_square(data, screen_x, screen_y, YELLOW);
			else
				fill_square(data, screen_x, screen_y, 0x222222);  // dark gray for floor/background

			border_square(data, screen_x, screen_y);
		}
	}
}


