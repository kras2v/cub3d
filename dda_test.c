/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/14 11:25:42 by valeriia         ###   ########.fr       */
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
	dda(data);
	draw_map_fill(data);
	// draw_map_border(data);
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

int	initialize_data(t_data **data)
{
	int	x;

	(*data) = malloc(sizeof(t_data));
	if ((*data) == NULL)
		return (1);
	(*data)->mlx = mlx_init();
	(*data)->mlx_win = mlx_new_window((*data)->mlx, WIDTH, HEIGHT, "cub3d");
	(*data)->img.ptr = mlx_new_image((*data)->mlx, WIDTH * 2, HEIGHT);
	(*data)->img.addr = mlx_get_data_addr((*data)->img.ptr, &(*data)->img.bits_per_pixel, &(*data)->img.line_length, &(*data)->img.endian);
	if (upload_textures((*data)))
		return (1);
	x = 0;
	while (x < WIDTH)
	{
		(*data)->normilized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	return (0);
}

bool is_possible_to_go_up(char **map, int *p_i, int *p_j, bool *closed)
{
	int	i;
	int	j;

	i = *p_i;
	j = *p_j;
	if (i - 1 >= 0 && map[i - 1][j] == '1')
	{
		i--;
		printf("\n");
		while (map[i][j] == '1' && i >= 0)
		{
			ft_printf("%c", map[i][j]);
			i--;
			if (i - 1 == 0 
				|| map[i][j] == ' ')
				break;
			if (map[i - 1][j] == '0')
				closed = false;
		}
	}
	*p_i = i;
	*p_j = j;
	return (0);
}

bool is_possible_to_go_left(char **map, int *p_i, int *p_j, bool *closed)
{
	int	i;
	int	j;

	i = *p_i;
	j = *p_j;
	if (j + 1 < MAP_HEIGHT - 1 && map[i][j + 1] == '1')
	{
		j++;
		printf("\n");
		while (map[i][j] == '1' && j < MAP_HEIGHT - 1)
		{
			ft_printf("%c", map[i][j]);
			j++;
			if (map[i][j + 1] == ' '
				|| j + 1 == MAP_HEIGHT - 1)
				break;
			if (map[i][j + 1] == '0')
			closed = false;
		}
	}
	*p_i = i;
	*p_j = j;
	return (0);
}

bool is_possible_to_go_right(char **map, int *p_i, int *p_j, bool *closed)
{
	int	i;
	int	j;

	i = *p_i;
	j = *p_j;
	if (j + 1 < MAP_HEIGHT - 1 && map[i][j + 1] == '1')
	{
		j++;
		while (map[i][j] == '1' && j < MAP_HEIGHT - 1)
		{
			ft_printf("%c", map[i][j]);
			j++;
			if (map[i][j + 1] == ' '
				|| j + 1 == MAP_HEIGHT - 1)
				break;
			if (map[i][j + 1] == '0')
			closed = false;
		}
	}
	*p_i = i;
	*p_j = j;
	return (0);
}

bool is_possible_to_go_down(char **map, int *p_i, int *p_j, bool *closed)
{
	int	i;
	int	j;

	i = *p_i;
	j = *p_j;
	if (i + 1 < MAP_WIDTH && map[i + 1][j] == '1')
	{
		i++;
		ft_printf("\n");
		while (map[i][j] == '1' && j < MAP_HEIGHT - 1)
		{
			ft_printf("%c", map[i][j]);
			j++;
			if (map[i][j + 1] == ' '
				|| j + 1 == MAP_HEIGHT - 1 )
				break;
			if (map[i][j + 1] == '0')
			closed = false;
		}
	}
	*p_i = i;
	*p_j = j;
	return (0);
}

void	skip_spaces(char **map, int *p_i, int *p_j, t_move direction)
{
	int	i;
	int	j;

	i = *p_i;
	j = *p_j;
	if (direction == RIGHT)
	{
		while (map[i][j] == ' ' && j < MAP_HEIGHT - 1)
		{
			ft_printf("%c", map[i][j]);
			if (map[i][j + 1] == '1' || map[i][j + 1] == '0')
				break;
			j++;
		}
	}
	if (direction == LEFT)
	{
		while (map[i][j] == ' ' && j >= 0)
		{
			ft_printf("%c", map[i][j]);
			if (map[i][j - 1] == '1' || map[i][j - 1] == '0')
				break;
			j--;
		}
	}
	if (direction == DOWN)
	{
		while (map[i][j] == ' ' && i < MAP_WIDTH - 1)
		{
			ft_printf("%c", map[i][j]);
			if (map[i + 1][j] == '1' || map[i + 1][j] == '0')
				break;
			i++;
		}
	}
	if (direction == UP)
	{
		while (map[i][j] == ' ' && i >= 0)
		{
			ft_printf("%c", map[i][j]);
			if (map[i - 1][j] == '1' || map[i - 1][j] == '0')
				break;
			i--;
		}
	}
	*p_i = i;
	*p_j = j;
}

bool	is_map_closed(char **map)
{
	t_coordinates	starting_point;
	int				i;
	int				j;
	bool			closed;

	i = 0;
	j = 0;
	closed = true;
	skip_spaces(map, &i, &j, RIGHT);
	starting_point.x = j;
	starting_point.x = i;
	while (true)
	{
		skip_spaces(map, &i, &j, RIGHT);
		while (closed == true)
		{
			is_possible_to_go_down(map, &i, &j, &closed);
			is_possible_to_go_right(map, &i, &j, &closed);
			is_possible_to_go_up(map, &i, &j, &closed);
		}
		
		if (1)
			break;
	}
	return (true);
}

int	main(int argc, char **args)
{
	t_data	*data;

	if (argc != 2)
		return (printf("wrong number of arguments\n"), 1);
	initialize_data(&data);
	if (!valid_input(args[1]))
		return (printf("invalid input\n"), 1);
	data->map = read_map(args[1]);
	if (!data->map)
		return (1);
	if (!map_valid(data))
		return(printf("Invalid input\n"), free_map_init(data->map), 1);
	int x = 0;
	while (x < WIDTH)
	{
		data->normilized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	init_player(data);
	display(data);
	init_hooks(data);
	mlx_loop(data->mlx);
	close_event(data);
	return (0);
}