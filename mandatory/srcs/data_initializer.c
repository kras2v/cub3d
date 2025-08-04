/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:19:23 by eklymova          #+#    #+#             */
/*   Updated: 2025/08/04 16:22:20 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	initialize_data(t_data *data)
{
	int	x;

	x = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->c = -1;
	data->f = -1;
	data->texture_params = NULL;
	data->script = NULL;
	data->mlx = NULL;
	data->map = NULL;
	data->texture_names = ft_calloc(5, sizeof(char *));
	data->texture_names = ft_calloc(5, sizeof(char *));
	data->door_last_open = 0;
	data->door_coordinates.x = 0;
	data->door_coordinates.y = 0;
	data->sprite = NULL;
	data->texture_names = ft_calloc(4, sizeof(char *));
	while (x < WIDTH)
	{
		data->normalized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	return (0);
}
