/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:25:25 by eklymova          #+#    #+#             */
/*   Updated: 2025/07/23 17:12:48 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda_bonus.h"

void	close_on_error(t_data *data, char *err_msg)
{
	if (err_msg == NULL)
		perror("cub3d: ");
	else
		ft_dprintf(2, err_msg);
	close_event(data);
}

void	free_mlx_data(void *mlx, void *img, void *mlx_win)
{
	if (img)
		mlx_destroy_image(mlx, img);
	if (mlx_win)
		mlx_destroy_window(mlx, mlx_win);
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	if (data->texture_params)
	{
		while (i < 4)
		{
			if (data->texture_params[i].image.ptr)
				mlx_destroy_image(data->mlx, data->texture_params[i].image.ptr);
			i++;
		}
		free(data->texture_params);
	}
	i = 0;
	if (data->texture_names)
	{
		while (i < 4)
		{
			if (data->texture_names[i])
				free(data->texture_names[i]);
			data->texture_names[i] = NULL;
			i++;
		}
	}
}

void	free_sprite(t_data *data)
{
	int	i;

	if (!data || !data->sprite)
		return ;
	i = 0;
	if (data->sprite->tex)
	{
		while (i < 2)
		{
			if (data->sprite->tex[i])
			{
				if (data->sprite->tex[i]->image.ptr)
					mlx_destroy_image(data->mlx,
						data->sprite->tex[i]->image.ptr);
				free(data->sprite->tex[i]);
			}
			i++;
		}
		free(data->sprite->tex);
	}
	free(data->sprite);
}
