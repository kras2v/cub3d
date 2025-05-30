/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriia <valeriia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/05/30 19:47:32 by valeriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	clear_display(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
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
	x = 0;
	while (x < PLAYER_SIZE)
	{
		y = 0;
		my_mlx_pixel_put(&(data->img), data->player.position.x + x, data->player.position.y + y, GREEN);
		while (y < PLAYER_SIZE)
		{
			my_mlx_pixel_put(&(data->img), data->player.position.x + x, data->player.position.y + y, GREEN);
			y++;
		}
		x++;
	}
	t_point new_point;
	new_point.x = data->player.position.x + data->player.direction.x * 50;
	new_point.y = data->player.position.y + data->player.direction.y * 50;
	printf("player: (%d, %d) |  a: (%d, %d) |  dir: (%f, %f)\n", data->player.position.x, data->player.position.y, new_point.x, new_point.y, data->player.direction.x, data->player.direction.y);
	draw_line(data, data->player.position, new_point);
}


void	fill_square(t_data *data, int px, int py)
{
	int	x;
	int	y;

	y = 0;
	while (y < CELL_SIZE)
	{
		x = 0;
		while (x < CELL_SIZE)
		{
			my_mlx_pixel_put(&(data->img), x + px, y + py, WHITE);
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

float	degrees_to_radian(int degrees)
{
	return ((PI / 180.0) * (float)degrees);
}

void	ccw_rotate(t_fvector *point, int degrees)
{
	t_fvector	temp;
	float	radian;

	temp.x = point->x;
	temp.y = point->y;
	radian = degrees_to_radian(degrees);
	point->x = (temp.x * cos(radian) - temp.y * sin(radian));
	point->y = (temp.x * sin(radian) + temp.y * cos(radian));
}

void	cw_rotate(t_fvector *point, int degrees)
{
	t_fvector	temp;
	float	radian;

	temp.x = point->x;
	temp.y = point->y;
	radian = degrees_to_radian(degrees);
	point->x = (temp.x * cos(radian) + temp.y * sin(radian));
	point->y = (temp.x * -sin(radian) + temp.y * cos(radian));
}

void	draw_map(t_data *data)
{
	int	px;
	int	py;

	py = 0;
	while (py < MAP_HEIGHT)
	{
		px = 0;
		while (px < MAP_WIDTH)
		{
			if (data->map[px][py] >= 1)
			{
				fill_square(data, px * CELL_SIZE, py * CELL_SIZE);
			}
			border_square(data,  px * CELL_SIZE, py * CELL_SIZE);
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

void	display(t_data *data)
{
	clear_display(data);
	draw_map(data);
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

int	move_player(int keycode, t_data *data)
{
	if (keycode == XK_W || keycode == XK_w)
	{
		data->player.position.y -= PLAYER_SIZE;
	}
	else if (keycode == XK_S || keycode == XK_s)
	{
		data->player.position.y += PLAYER_SIZE;
	}
	else if (keycode == XK_D || keycode == XK_d)
	{
		data->player.position.x += PLAYER_SIZE;
	}
	else if (keycode == XK_A || keycode == XK_a )
	{
		data->player.position.x -= PLAYER_SIZE;
	}
	else if (keycode == XK_Left)
	{
		ccw_rotate(&(data->player.direction), 1);
	}
	else if (keycode == XK_Right)
	{
		cw_rotate(&(data->player.direction), 1);
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

void	init_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, ON_DESTROY, NO_EVENT_MASK, close_event, data);
	mlx_hook(data->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_event, data);
}

void	init_player(t_data *data)
{
	data->player.position.x = WIDTH / 2 + PLAYER_SIZE / 2;
	data->player.position.y = HEIGHT / 2 + PLAYER_SIZE / 2;
	data->player.rotation_angle = 0;
	data->player.delta_position.x = 0;
	data->player.delta_position.y = 0;
	data->player.direction.x = 1;
	data->player.direction.y = 0;
	data->player.plane.x = 0;
	data->player.plane.y = 0.66;
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

int	main(void)
{
	t_data	*data;

	int worldMap[MAP_WIDTH][MAP_HEIGHT]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	data->map = malloc(sizeof(int *) * MAP_HEIGHT);
	if (data->map == NULL)
	{
		close_event(data);
	}
	int i = 0;
	while (i < MAP_HEIGHT)
	{
		data->map[i] = malloc(sizeof(int) * MAP_WIDTH);
		if (data->map[i] == NULL)
		{
			free_map(data->map, i);
		}
		int j = 0;
		while (j < MAP_WIDTH)
		{
			data->map[i][j] = worldMap[i][j];
			j++;
		}
		i++;
	}
	print_map(data->map);
	init_player(data);
	display(data);
	draw_map(data);
	init_hooks(data);
	mlx_loop(data->mlx);
	return (0);
}