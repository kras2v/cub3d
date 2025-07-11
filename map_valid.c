/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:26 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/11 15:19:35 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool	invalid_char(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == WALL || data->map[y][x] == WEST
				|| data->map[y][x] == EAST || data->map[y][x] == EMPTY
				|| data->map[y][x] == NORTH || data->map[y][x] == SOUTH
				|| data->map[y][x] == ' ')
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

bool	map_valid(t_data	*data)
{
	if (!data->N_T || !data->S_T || !data->E_T || !data->W_T || !data->C || !data->F)
		return (printf("Error: texture paths are missing\n"), false);
	if (!char_counter(data))
		return (false);
	if (!invalid_char(data))
		return (false);
	return (true);
}
