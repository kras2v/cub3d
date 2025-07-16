/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:24:18 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/16 22:40:53 by valeriia         ###   ########.fr       */
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
	int map_width,
	int map_height,
	char **map,
	t_coordinates map_coords
)
{
	int	color;

	color = BLACK;
	if (map_coords.x < 0 || map_coords.y < 0
		|| map_coords.x >= map_width || map_coords.y >= map_height
		|| map[map_coords.y][map_coords.x] == SPACE)
		color = DARK_GRAY;
	else if (map[map_coords.y][map_coords.x] == WALL)
		color = YELLOW;
	return (color);
}

void	draw_map_fill(t_data *data)
{
	t_coordinates	coordinates;
	t_coordinates	map;
	t_colors		color;

	coordinates.y = 0;
	coordinates.x = 0;
	color = BLACK;
	while (coordinates.y < MINIMAP_OFFSET_Y)
	{
		coordinates.x = 0;
		while (coordinates.x < MINIMAP_OFFSET_X)
		{
			map.x = (int)data->player.position.x - MINIMAP_RADIUS + coordinates.x;
			map.y = (int)data->player.position.y - MINIMAP_RADIUS + coordinates.y;
			color = get_square_color(data->map_width, data->map_height, data->map, map);
			fill_square(data, coordinates.x * MINI_TILE, coordinates.y * MINI_TILE, color);
			border_square(data, coordinates.x * MINI_TILE, coordinates.y * MINI_TILE);
			coordinates.x++;
		}
		coordinates.y++;
	}
}
