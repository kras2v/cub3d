/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/16 21:29:56 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool	is_direction(int coordinate)
{
	return (coordinate == NORTH
		|| coordinate == EAST
		|| coordinate == SOUTH
		|| coordinate == WEST);
}

int	display(t_data *data)
{
	dda(data);
	draw_map_fill(data);
	draw_flashlight(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (1);
}

int upload_textures(t_data *data)
{
	int	i;

	i = 0;
	data->texture = ft_calloc(4, sizeof(t_texture));
	//!CHECK MALLOC
	while (i < 4)
	{
		if (i == N)
			data->texture[i].name = data->n_t;
		else if (i == E)
			data->texture[i].name = data->e_t;
		else if (i == S)
			data->texture[i].name = data->s_t;
		else if (i == W)
			data->texture[i].name = data->w_t;
		data->texture[i].image.ptr = mlx_xpm_file_to_image(data->mlx, data->texture[i].name, &data->texture[i].width, &data->texture[i].height);
		if (data->texture[i].image.ptr == NULL)
		{
			printf("Error occured while converting file to image\n");
			close_event(data);
		}
		data->texture[i].image.addr = mlx_get_data_addr(data->texture[i].image.ptr, &data->texture[i].image.bits_per_pixel,
				&data->texture[i].image.line_length, &data->texture[i].image.endian);
		i++;
	}
	return (0);
}

int	initialize_data(t_data *data)
{
	int x;

	x = 0;
	data->map_height = 0;
	data->map_width = 0;
	while (x < WIDTH)
	{
		data->normalized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	return (0);
}

void	start_mlx(
	t_data *data
)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}

int	main(int argc, char **args)
{
	t_data	data;

	if (argc != 2)
		return (printf("wrong number of arguments\n"), 1);
	if (!valid_input(args[1]))
		return (printf("invalid input\n"), 1);
	initialize_data(&data);
	data.script = read_map(args[1]);
	if (!data.script)
		return (1);
	if (!is_script_valid(&data))
		return(printf("Invalid input\n"), close_event(&data));
	if (!map_valid(&data))
		return(printf("Invalid input\n"), close_event(&data));
	start_mlx(&data);
	init_hooks(&data);
	if (upload_textures(&data))
		return(printf("Invalid input\n"), close_event(&data));
	init_player(&data);
	mlx_loop_hook(data.mlx, &display, &data);
	mlx_loop(data.mlx);
	close_event(&data);
	return (0);
}
