/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:16:21 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 18:19:58 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

int	initialize_data(t_data *data)
{
	int	x;

	x = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->c = -1;
	data->f = -1;
	data->texture = NULL;
	data->script = NULL;
	data->mlx = NULL;
	data->map = NULL;
	data->n_t = NULL;
	data->e_t = NULL;
	data->w_t = NULL;
	data->s_t = NULL;
	data->door_last_open = 0;
	data->door_coordinates.x = 0;
	data->door_coordinates.y = 0;
	data->door = "./walls/xpm/dooor.xpm";
	data->sprite = NULL;
	while (x < WIDTH)
	{
		data->normalized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	return (0);
}
