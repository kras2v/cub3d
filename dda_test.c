/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/15 18:32:46 by kvalerii         ###   ########.fr       */
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

void	compute_dir(t_fvector *dir, t_fvector player_dir, double angle)
{
	dir->x = player_dir.x * cos(angle) - player_dir.y * sin(angle);
	dir->y = player_dir.x * sin(angle) + player_dir.y * cos(angle);
}

t_fvector	cast_flashlight_ray(t_data *data, t_fvector dir,
		int map_start_x, int map_start_y)
{
	t_fvector	pos;
	t_fvector	end;
	double		len;
	size_t		mx;
	size_t		my;

	pos = data->player.position;
	len = 0;
	while (len < 2.0)
	{
		mx = (int)pos.x;
		my = (int)pos.y;
		if (my >= 0 && my < data->map_height && mx >= 0
			&& mx < data->map_width && data->map[my][mx] == WALL)
			break ;
		pos.x += dir.x * 0.1;
		pos.y += dir.y * 0.1;
		len += 0.1;
	}
	end.x = (pos.x - map_start_x) * MINI_TILE;
	end.y = (pos.y - map_start_y) * MINI_TILE;
	return (end);
}

void	draw_flashlight(t_data *data)
{
	t_flash_params	param;
	t_fvector		dir;
	t_fvector		end;
	int				i;
	double			a;

	param.map_start_x = (int)data->player.position.x - MINIMAP_RADIUS;
	param.map_start_y = (int)data->player.position.y - MINIMAP_RADIUS;
	param.player_pos.x = (data->player.position.x
			- param.map_start_x) * MINI_TILE;
	param.player_pos.y = (data->player.position.y
			- param.map_start_y) * MINI_TILE;
	param.fov = 1;
	param.rays = 120;
	param.step_angle = param.fov / (param.rays - 1);
	param.start = -param.fov / 2;
	i = 0;
	while (i++ < param.rays)
	{
		a = param.start + i * param.step_angle;
		compute_dir(&dir, data->player.direction, a);
		end = cast_flashlight_ray(data, dir, param.map_start_x,
				param.map_start_y);
		draw_line(data, param.player_pos, end, WHITE);
	}
}

int	display(t_data *data)
{
	dda(data);
	draw_map_fill(data);
	draw_player(data);
	draw_flashlight(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	return (1);
}

void	init_player(t_data *data)
{
	size_t	y;
	size_t	x;
	bool	is_position_set;

	y = 0;
	data->player.plane.x = 0;
	data->player.plane.y = 0;
	is_position_set = false;
	while (y < data->map_height && is_position_set == false)
	{
		x = 0;
		while (x < data->map_width && is_position_set == false)
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
			if (is_position_set)
				break;
			x++;
		}
		if (is_position_set)
			break;
		y++;
	}
	data->player.position.x = x + 0.5;
	data->player.position.y = y + 0.5;
	data->player.plane.x = -data->player.direction.y * FOV;
	data->player.plane.y = data->player.direction.x * FOV;
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
			data->texture[i].name = data->N_T;
		else if (i == E)
			data->texture[i].name = data->E_T;
		else if (i == S)
			data->texture[i].name = data->S_T;
		else if (i == W)
			data->texture[i].name = data->W_T;
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

int	initialize_data(t_data **data)
{
	(*data) = ft_calloc(1, sizeof(t_data));
	if ((*data) == NULL)
		return (1);
	(*data)->mlx = mlx_init();
	(*data)->mlx_win = mlx_new_window((*data)->mlx, WIDTH, HEIGHT, "cub3d");
	(*data)->img.ptr = mlx_new_image((*data)->mlx, WIDTH, HEIGHT);
	(*data)->img.addr = mlx_get_data_addr((*data)->img.ptr, &(*data)->img.bits_per_pixel, &(*data)->img.line_length, &(*data)->img.endian);
	(*data)->map_height = 0;
	(*data)->map_width = 0;
	int x = 0;
	while (x < WIDTH)
	{
		(*data)->normilized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
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
	data->script = read_map(args[1]);
	if (!data->script)
		return (1);
	script_init(data);
	if (!map_valid(data))
		return(printf("Invalid input\n"), close_event(data));
	if (upload_textures(data))
		return(printf("Invalid input\n"), close_event(data));
	//!init mlx
	init_player(data);
	init_hooks(data);
	mlx_loop_hook(data->mlx, &display, data);
	mlx_loop(data->mlx);
	close_event(data);
	return (0);
}
