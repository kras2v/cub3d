/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:17:37 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/22 14:06:29 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

static char	*choose_texture_name(t_data *data, int i)
{
	if (i == N)
		return (data->n_t);
	else if (i == E)
		return (data->e_t);
	else if (i == S)
		return (data->s_t);
	else if (i == W)
		return (data->w_t);
	else if (i == D)
		return (data->door);
	return (NULL);
}

static void	convert_file_to_mlx_image(
	t_data *data,
	int texture_number
)
{
	char	*file_name;

	file_name = choose_texture_name(data, texture_number);
	data->texture[texture_number].image.ptr = mlx_xpm_file_to_image(
			data->mlx,
			file_name,
			&data->texture[texture_number].width,
			&data->texture[texture_number].height);
	if (data->texture[texture_number].image.ptr == NULL)
	{
		close_on_error(data, NULL);
	}
}

static void	get_image_data_address(
	t_data *data,
	int texture_number
)
{
	data->texture[texture_number].image.addr = mlx_get_data_addr(
			data->texture[texture_number].image.ptr,
			&data->texture[texture_number].image.bits_per_pixel,
			&data->texture[texture_number].image.line_length,
			&data->texture[texture_number].image.endian);
	if (data->texture[texture_number].image.addr == NULL)
	{
		close_on_error(data, NULL);
	}
}

static int	upload_textures(t_data *data)
{
	int		texture_number;

	texture_number = 0;
	data->texture = ft_calloc(5, sizeof(t_texture));
	if (data->texture == NULL)
	{
		return (close_on_error(data, NULL), 1);
	}
	while (texture_number < 5)
	{
		convert_file_to_mlx_image(data, texture_number);
		get_image_data_address(data, texture_number);
		texture_number++;
	}
	return (0);
}

void	start_mlx(
	t_data *data
)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		close_on_error(data, NULL);
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	if (!data->mlx_win)
		close_on_error(data, NULL);
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.ptr)
		close_on_error(data, NULL);
	data->img.addr = mlx_get_data_addr(
			data->img.ptr,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);
	if (!data->img.addr)
		close_on_error(data, NULL);
	init_hooks(data);
	upload_textures(data);
}
