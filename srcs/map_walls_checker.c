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

static bool	is_map_closed(t_data *data, int x, int y)
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
