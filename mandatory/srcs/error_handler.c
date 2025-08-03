/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:05:28 by kvalerii          #+#    #+#             */
/*   Updated: 2025/08/03 09:43:05 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

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
}
