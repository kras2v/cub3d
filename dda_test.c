/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/26 15:05:32 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

bool is_direction(int coordinate)
{
	return (coordinate == NORTH
		|| coordinate == EAST
		|| coordinate == SOUTH
		|| coordinate == WEST);
}

void	display(t_data *data)
{
	clear_display(data);
	draw_map_border(data);
	dda(data);
	draw_map_fill(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

void	init_player(t_data *data)
{
	int		y;
	int		x;
	bool	is_position_set;

	y = 0;
	data->player.plane.x = 0;
	data->player.plane.y = 0;
	is_position_set = false;
	while (y < MAP_HEIGHT && is_position_set == false)
	{
		x = 0;
		while (x < MAP_WIDTH && is_position_set == false)
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'E' || data->map[y][x] == 'S' || data->map[y][x] == 'W')
			{
				is_position_set = true;
				if (data->map[y][x] == 'N')
				{
					data->player.direction.x = 0;
					data->player.direction.y = -1;
				}
				else if (data->map[y][x] == 'E')
				{
					data->player.direction.x = 1;
					data->player.direction.y = 0;
				}
				else if (data->map[y][x] == 'S')
				{
					data->player.direction.x = 0;
					data->player.direction.y = 1;
				}
				else if (data->map[y][x] == 'W')
				{
					data->player.direction.x = -1;
					data->player.direction.y = 0;
				}
			}
			x++;
		}
		y++;
	}
	data->player.position.x = x;
	data->player.position.y = y;
	data->player.plane.x = -data->player.direction.y * FOV;
	data->player.plane.y = data->player.direction.x * FOV;
}

int upload_textures(t_data *data)
{
	int	i;

	i = 0;
	data->texture = malloc(sizeof(t_texture) * 4);
	//!CHECK MALLOC
	while (i < 4)
	{
		if (i == N)
			data->texture[i].name = "./walls/xpm/north_wall.xpm";
		else if (i == E)
			data->texture[i].name = "./walls/xpm/east_wall.xpm";
		else if (i == S)
			data->texture[i].name = "./walls/xpm/south_wall.xpm";
		else if (i == W)
			data->texture[i].name = "./walls/xpm/west_wall.xpm";
		data->texture[i].image.ptr = mlx_xpm_file_to_image(data->mlx, data->texture[i].name, &data->texture[i].width, &data->texture[i].height);
		if (data->texture[i].image.ptr == NULL)
		{
			printf("Error occured while converting file to image\n");
			return (1);
		}
		else
		{
			printf("Image size %dx%d\n", data->texture[i].width, data->texture[i].height);
		}
		data->texture[i].image.addr = mlx_get_data_addr(data->texture[i].image.ptr, &data->texture[i].image.bits_per_pixel,
				&data->texture[i].image.line_length, &data->texture[i].image.endian);
		i++;
	}
	return (0);
}

// void	add_map(t_data **data)
// {
// 	int worldMap[MAP_WIDTH][MAP_HEIGHT]=
// 	{
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
// 		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,'S',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 	};
	
// 	(*data)->map = malloc(sizeof(int *) * MAP_HEIGHT);
// 	if ((*data)->map == NULL)
// 	{
// 		close_event((*data));
// 	}
// 	int i = 0;
// 	while (i < MAP_HEIGHT)
// 	{
// 		(*data)->map[i] = malloc(sizeof(int) * MAP_WIDTH);
// 		if ((*data)->map[i] == NULL)
// 		{
// 			free_map((*data)->map, i);
// 		}
// 		int j = 0;
// 		while (j < MAP_WIDTH)
// 		{
// 			(*data)->map[i][j] = worldMap[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// }

int	initialize_data(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
	if ((*data) == NULL)
		return (1);
	(*data)->mlx = mlx_init();
	(*data)->mlx_win = mlx_new_window((*data)->mlx, WIDTH * 2, HEIGHT, "cub3d");
	(*data)->img.ptr = mlx_new_image((*data)->mlx, WIDTH * 2, HEIGHT);
	(*data)->img.addr = mlx_get_data_addr((*data)->img.ptr, &(*data)->img.bits_per_pixel, &(*data)->img.line_length, &(*data)->img.endian);
	if (upload_textures((*data)))
		return (1);
	// add_map(data);
	return (0);
}

int	main(int argc, char **args)
{
	t_data	*data;

	if (argc != 2)
		return (printf("wrong number of arguments\n"), 1);
	if (!valid_input(args[1]))
		return (printf("invalid input\n"), 1);
	initialize_data(&data);
	data->map = read_map(args[1]);
	if (!data->map)
		return (1);
	int x = 0;
	while (x < WIDTH)
	{
		data->normilized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	init_player(data);
	display(data);
	printf("hello\n");
	init_hooks(data);
	mlx_loop(data->mlx);
	close_event(data);
	return (0);
}