/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/06/25 19:43:12 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clear_display(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = WIDTH;
		while (x < WIDTH * 2)
		{
			my_mlx_pixel_put(&(data->img), x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		my_mlx_pixel_put(&(data->img), ((data->player.position.x) * CELL_SIZE  - PLAYER_SIZE / 2 + x) + WIDTH - 1, ((data->player.position.y) * CELL_SIZE  - PLAYER_SIZE / 2 + y), GREEN);
		while (x < PLAYER_SIZE)
		{
			my_mlx_pixel_put(&(data->img), ((data->player.position.x) * CELL_SIZE  - PLAYER_SIZE / 2 + x) + WIDTH - 1, ((data->player.position.y) * CELL_SIZE  - PLAYER_SIZE / 2 + y), GREEN);
			x++;
		}
		y++;
	}
}

void	fill_square(t_data *data, int px, int py, t_colors color)
{
	int	x;
	int	y;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			my_mlx_pixel_put(&(data->img), x + px, y + py, color);
			x++;
		}
		y++;
	}
}

void	border_square(t_data *data, int px, int py)
{
	int	x;
	int	y;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			if ((y == 0 || y == CELL_SIZE - 1)
			|| (x == 0 || x == CELL_SIZE - 1))
			{
				my_mlx_pixel_put(&(data->img), x + px, y + py, PURPLE);
			}
			x++;
		}
		y++;
	}
}

void	rotate(t_fvector *point, double radian)
{
	t_fvector	temp;

	temp.x = point->x;
	temp.y = point->y;
	point->x = (temp.x * cos(radian) - temp.y * sin(radian));
	point->y = (temp.x * sin(radian) + temp.y * cos(radian));
}

bool is_direction(int coordinate)
{
	return (coordinate == NORTH
		|| coordinate == EAST
		|| coordinate == SOUTH
		|| coordinate == WEST);
}

void	draw_map_fill(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MAP_HEIGHT)
	{
		px = 0;
		while (px < MAP_WIDTH)
		{
			if (data->map[py][px] >= 1 && !is_direction(data->map[py][px]))
			{
				t_colors color;
				switch(data->map[py][px])
				{
					case 1:  color = YELLOW;  break;
					case 2:  color = GREEN;  break;
					case 3:  color = BLUE;   break;
					case 4:  color = RED;  break;
					default: color = WHITE; break;
				}
				fill_square(data, px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE, color);
				border_square(data,  px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE);
			}
			px++;
		}
		py++;
	}
}

void	draw_map_border(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MAP_HEIGHT)
	{
		px = 0;
		while (px < MAP_WIDTH)
		{
			if (data->map[py][px] >= 1 && !is_direction(data->map[py][px]))
			{
				t_colors color;
				switch(data->map[py][px])
				{
					case 1:  color = YELLOW;  break;
					case 2:  color = GREEN;  break;
					case 3:  color = BLUE;   break;
					case 4:  color = RED;  break;
					default: color = WHITE; break;
				}
				fill_square(data, px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE, color);
			}
			border_square(data,  px * CELL_SIZE + WIDTH - 1, py * CELL_SIZE);
			px++;
		}
		py++;
	}}

void	display(t_data *data)
{
	clear_display(data);
	draw_map_border(data);
	dda(data);
	draw_map_fill(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

int	close_event(t_data *data)
{
	if (data && data->mlx)
	{
		if (data->img.ptr)
			mlx_destroy_image(data->mlx, data->img.ptr);
		if (data->mlx_win)
			mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data);
	}
	exit(0);
	return(0);
}

bool	is_wall(t_data *data, double shift_x, double shift_y)
{
	double	player_size_in_cell;

	player_size_in_cell = ((double)PLAYER_SIZE / 2.0) / (double)CELL_SIZE;
	if (data->map[(int)(data->player.position.y - player_size_in_cell + shift_y)][(int)(data->player.position.x - player_size_in_cell + shift_x)] == WALL
		|| data->map[(int)(data->player.position.y - player_size_in_cell + shift_y)][(int)(data->player.position.x + player_size_in_cell + shift_x)] == WALL
		|| data->map[(int)(data->player.position.y + player_size_in_cell +  shift_y)][(int)(data->player.position.x + player_size_in_cell +  shift_x)] == WALL
		|| data->map[(int)(data->player.position.y + player_size_in_cell +  shift_y)][(int)(data->player.position.x - player_size_in_cell +  shift_x)] == WALL)
	{
		return (true);
	}
	return (false);
}

void	slide(t_data *data, double shift_x, double shift_y, double move_speed)
{
	if (is_wall(data, shift_x * move_speed, 0) == false)
		data->player.position.x += shift_x * move_speed;
	if (is_wall(data, 0, shift_y * move_speed) == false)
		data->player.position.y += shift_y * move_speed;
}

int	move_player(int keycode, t_data *data)
{
	static struct timeval	old_time;
	static struct timeval	now_time;
	double					frame_time;
	double					move_speed;
	double					rot_speed;
	double					shift_x;
	double					shift_y;

	if (now_time.tv_sec == 0)
	{
		gettimeofday(&now_time, 0);
	}
	old_time = now_time;
	gettimeofday(&now_time, 0);
	frame_time = (now_time.tv_sec - old_time.tv_sec) + (now_time.tv_usec - old_time.tv_usec) / 1000000.0;
	if (frame_time > 0.1)
		printf("FPS %f\n", 1.0 / frame_time);
	if (frame_time > 0.2)
		frame_time = 0.2;
	display(data);

	move_speed = 0.3;
	rot_speed = frame_time * 3.0;

	shift_x = 0;
	shift_y = 0;
	if (keycode == XK_W || keycode == XK_w)
	{
		shift_x += data->player.direction.x * move_speed;
		shift_y += data->player.direction.y * move_speed;
	}
	if (keycode == XK_S || keycode == XK_s)
	{
		shift_x -= data->player.direction.x * move_speed;
		shift_y -= data->player.direction.y * move_speed;
	}
	if (keycode == XK_A || keycode == XK_a)
	{
		shift_x += data->player.direction.y * move_speed;
		shift_y += -data->player.direction.x * move_speed;
	}
	if (keycode == XK_D || keycode == XK_d)
	{
		shift_x += -data->player.direction.y * move_speed;
		shift_y += data->player.direction.x * move_speed;
	}

	slide(data, shift_x, shift_y, move_speed);

	if (keycode == XK_Left)
	{
		rotate(&(data->player.direction), -rot_speed);
		rotate(&(data->player.plane), -rot_speed);
	}
	else if (keycode == XK_Right)
	{
		rotate(&(data->player.direction), rot_speed);
		rotate(&(data->player.plane), rot_speed);
	}
	return (0);
}

int	key_press_event(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		close_event(data);
	}
	if ((keycode == XK_W || keycode == XK_w)
		|| (keycode == XK_S || keycode == XK_s)
		|| (keycode == XK_D || keycode == XK_d)
		|| (keycode == XK_A || keycode == XK_a )
		|| (keycode == XK_Right || keycode == XK_Left))
	{
		move_player(keycode, data);
		display(data);
	}
	return (0);
}


int print_coords(int button, int x, int y, t_data *param)
{
	(void)param;
	(void)button;
	printf("px: %d | py: %d | map_x: %d | map_y: %d | is_wall: %d|\n", x - WIDTH, y, ( x - WIDTH) / CELL_SIZE, y / CELL_SIZE, param->map[y / CELL_SIZE][(x - WIDTH) / CELL_SIZE] > 0
		&& !is_direction(param->map[y / CELL_SIZE][(x - WIDTH) / CELL_SIZE]));
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, ON_DESTROY, NO_EVENT_MASK, close_event, data);
	mlx_mouse_hook(data->mlx_win, print_coords, data);
	mlx_hook(data->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_event, data);
}

void	init_player2(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->player.plane.x = 0;
	data->player.plane.y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (data->map[y][x] == 'N')
			{
				data->player.direction.x = 0;
				data->player.direction.y = -1;
				data->player.position.x = x;
				data->player.position.y = y;
			}
			else if (data->map[y][x] == 'E')
			{
				data->player.direction.x = 1;
				data->player.direction.y = 0;
				data->player.position.x = x;
				data->player.position.y = y;
			}
			else if (data->map[y][x] == 'S')
			{
				data->player.direction.x = 0;
				data->player.direction.y = 1;
				data->player.position.x = x;
				data->player.position.y = y;
			}
			else if (data->map[y][x] == 'W')
			{
				data->player.direction.x = -1;
				data->player.direction.y = 0;
				data->player.position.x = x;
				data->player.position.y = y;
			}
			x++;
		}
		y++;
	}
	// printf("player pos: %f %f\n", data->player.position.x)
	data->player.plane.x = 0.66;
	data->player.plane.y = 0;
}

void	free_map(int **map, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		free(map[j]);
		j++;
	}
	free(map);
}

void	print_map(int **map)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			printf("%d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
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

void	add_map(t_data **data)
{
	int worldMap[MAP_WIDTH][MAP_HEIGHT]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,'N',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	(*data)->map = malloc(sizeof(int *) * MAP_HEIGHT);
	if ((*data)->map == NULL)
	{
		close_event((*data));
	}
	int i = 0;
	while (i < MAP_HEIGHT)
	{
		(*data)->map[i] = malloc(sizeof(int) * MAP_WIDTH);
		if ((*data)->map[i] == NULL)
		{
			free_map((*data)->map, i);
		}
		int j = 0;
		while (j < MAP_WIDTH)
		{
			(*data)->map[i][j] = worldMap[i][j];
			j++;
		}
		i++;
	}
}

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
	add_map(data);
	return (0);
}

int	main(void)
{
	t_data	*data;

	initialize_data(&data);
	int x = 0;
	while (x < WIDTH)
	{
		data->normilized_x[x] = (2.0 * (double)x / (double)WIDTH) - 1.0;
		x++;
	}
	init_player2(data);
	// print_map(data->map);
	// dda(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	display(data);
	init_hooks(data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_image(data->mlx, data->texture->image.ptr);
	mlx_clear_window(data->mlx, data->mlx_win);
	free(data->mlx);
	free_map(data->map, MAP_HEIGHT);
	free(data);
	return (0);
}