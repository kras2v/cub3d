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
	int		x;
	int		y;
	double	px;
	double	py;

	y = 0;
	px = (data->player.position.x - ((int)data->player.position.x - MINIMAP_RADIUS)) * MINI_TILE;
	py = (data->player.position.y - ((int)data->player.position.y - MINIMAP_RADIUS)) * MINI_TILE;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			my_mlx_pixel_put(&(data->img),
				(int)(px - PLAYER_SIZE / 2 + x),
				(int)(py - PLAYER_SIZE / 2 + y),
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
	while (y < MINI_TILE)
	{
		x = 0;
		while (x < MINI_TILE)
		{
			if ((y == 0 || y == MINI_TILE + 1) || (x == 0 || x == MINI_TILE + 1))
			{
				my_mlx_pixel_put(&(data->img), x + px, y + py, PURPLE);
			}
			x++;
		}
		y++;
	}
}

void	draw_map_border(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MINI_TILE)
	{
		px = 0;
		while (px < MINI_TILE)
		{
			border_square(data,  px * MINI_TILE, py * MINI_TILE);
			px++;
		}
		py++;
	}
}

void	draw_map_fill(t_data *data)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	y = 0;
	while (y < MINIMAP_OFFSET_Y)
	{
		x = 0;
		while (x < MINIMAP_OFFSET_X)
		{
			map_x = (int)data->player.position.x - MINIMAP_RADIUS + x;
			map_y = (int)data->player.position.y - MINIMAP_RADIUS + y;
			if (map_x < 0 || map_y < 0 || map_x >= MAP_WIDTH || map_y >= MAP_HEIGHT
				|| !data->map[map_y] || data->map[map_y][map_x] == ' ')
				fill_square(data, x * MINI_TILE, y * MINI_TILE, DARK_GRAY);
			else if (data->map[map_y][map_x] == WALL)
				fill_square(data, x * MINI_TILE, y * MINI_TILE, YELLOW);
			else
				fill_square(data, x * MINI_TILE, y * MINI_TILE, BLACK);

			border_square(data, x * MINI_TILE, y * MINI_TILE);
			x++;
		}
		y++;
	}
}
