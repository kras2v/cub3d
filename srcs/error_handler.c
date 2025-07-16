/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:57:51 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 13:58:13 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

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
	if (data->texture)
	{
		while (i < 4)
		{
			if (data->texture[i].image.ptr)
				mlx_destroy_image(data->mlx, data->texture[i].image.ptr);
			i++;
		}
		free(data->texture);
	}
	if (data->n_t)
		free(data->n_t);
	if (data->s_t)
		free(data->s_t);
	if (data->e_t)
		free(data->e_t);
	if (data->w_t)
		free(data->w_t);
}
