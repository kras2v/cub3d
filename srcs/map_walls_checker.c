/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:26 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/22 14:06:02 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool	invalid_char(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == WALL || data->map[y][x] == WEST
				|| data->map[y][x] == EAST || data->map[y][x] == EMPTY
				|| data->map[y][x] == NORTH || data->map[y][x] == SOUTH
				|| data->map[y][x] == SPACE || data->map[y][x] == SPRIT)
				x++;
			else
				return (0);
		}
		y++;
	}
	return (1);
}

int	counter(char **map, char c)
{
	int	y;
	int	x;
	int	counter;

	counter = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
				counter++;
			x++;
		}
		y++;
	}
	return (counter);
}

bool	char_counter(t_data *data)
{
	int	count;

	count = 0;
	count += counter(data->map, EAST);
	count += counter(data->map, WEST);
	count += counter(data->map, SOUTH);
	count += counter(data->map, NORTH);
	if (count != 1)
		return (false);
	return (true);
}

bool	is_map_closed(t_data *data, size_t x, size_t y)
{
	if (y >= data->map_height || x >= data->map_width || y < 0 || x < 0)
		return (false);
	if (data->map[y][x] == SPACE)
		return (false);
	if (data->map[y][x] == WALL || data->map[y][x] == 'V')
		return (true);
	if (data->map[y][x] != EMPTY && !is_direction(data->map[y][x]))
		return (true);
	if (data->map[y][x] == EMPTY)
		data->map[y][x] = 'V';
	return (is_map_closed(data, x - 1, y) && is_map_closed(data, x, y - 1)
		&& is_map_closed(data, x + 1, y) && is_map_closed(data, x, y + 1));
	return (true);
}

static void	replace_visited_with_empty(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'V')
			{
				data->map[y][x] = EMPTY;
			}
			x++;
		}
		y++;
	}
}

bool	check_map_walls(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == EMPTY || is_direction(data->map[y][x]))
			{
				if (is_map_closed(data, x, y) == false)
					return (false);
			}
			x++;
		}
		y++;
	}
	replace_visited_with_empty(data);
	return (true);
}
