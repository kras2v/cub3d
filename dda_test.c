/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:10 by kvalerii          #+#    #+#             */
/*   Updated: 2025/05/19 17:47:19 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx_img
{
	void *mlx;
	void *mlx_win;
	t_data img;
} t_mlx_img;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int loop_hook(void *param)
{
	int vMouse[2] = {0};

	t_mlx_img data = *((t_mlx_img *)param);
	mlx_mouse_get_pos(data.mlx, data.mlx_win, &vMouse[0], &vMouse[1]);
	my_mlx_pixel_put(&data.img, vMouse[0], vMouse[1], 0x00FF0000);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img.img, 0, 0);
	return (0);
}

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_mlx_img	mlx_img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop_hook(mlx_img.mlx, loop_hook, &mlx_img);
	mlx_loop(mlx);
}