/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 14:17:26 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	draw_player(t_data *data)
{
	int		x;
	int		y;
	double	px;
	double	py;

	y = -PLAYER_SIZE / 2;
	px = convert_to_minimap_coordinates(data->player.position.x);
	py = convert_to_minimap_coordinates(data->player.position.y);
	while (y < PLAYER_SIZE / 2)
	{
		x = -PLAYER_SIZE / 2;
		while (x < PLAYER_SIZE / 2)
		{
			my_mlx_pixel_put(&(data->img), (int)(px + x), (int)(py + y), GREEN);
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
			border_square(data, px * MINI_TILE, py * MINI_TILE);
			px++;
		}
		py++;
	}
}

int	get_square_color(
	t_data *data,
	char **map,
	t_coordinates map_coords
)
{
	int	color;

	color = BLACK;
	if (map_coords.x < 0 || map_coords.y < 0
		|| map_coords.x >= data->map_width
		|| map_coords.y >= data->map_height
		|| map[map_coords.y][map_coords.x] == SPACE)
		color = DARK_GRAY;
	else if (is_wall(map[map_coords.y][map_coords.x])
		|| is_door(map[map_coords.y][map_coords.x]))
		color = YELLOW;
	else if (is_sprite(map[map_coords.y][map_coords.x]))
		color = PINK;
	return (color);
}

int	get_minimum_tile(double position)
{
	return ((int)position - MINIMAP_RADIUS);
}

void	draw_map_fill(t_data *data)
{
	t_coordinates	coordinates;
	t_coordinates	map;
	t_colors		color;

	color = BLACK;
	coordinates.y = 0;
	coordinates.x = 0;
	while (coordinates.y < MINIMAP_OFFSET_Y)
	{
		coordinates.x = 0;
		while (coordinates.x < MINIMAP_OFFSET_X)
		{
			map.x = get_minimum_tile(data->player.position.x) + coordinates.x;
			map.y = get_minimum_tile(data->player.position.y) + coordinates.y;
			color = get_square_color(data, data->map, map);
			fill_square(data, coordinates.x, coordinates.y, color);
			border_square(data, coordinates.x, coordinates.y);
			coordinates.x++;
		}
		coordinates.y++;
	}
}
