/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:36 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/03 22:09:51 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fractol.h"


int32_t	ft_pixel(int iter, char color)
{
	t_color	rgba;
	if (color == 'p')
	{
		rgba.r = 0 + (iter * 14);
		rgba.g = 0 + (iter * 6);
		rgba.b = 0 + (iter * 10);
	}
	if (color == 'd')
	{
		rgba.r = 0;
		rgba.g = 191;
		rgba.b = 255;
	}
	return (rgba.r << 24 | rgba.g << 16 | rgba.b << 8 | 255);
}

int	is_in_mandelbrot(u_int32_t i, u_int32_t y)
{
	t_coords	z;
	t_coords	c;
	int			current_iter;
	t_data		*data;

	data = get_data_ptr();
	current_iter = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (scale_to_map(i, -2, +2, WIDTH) * data->zoom) + data->shift_x;
	c.y = (scale_to_map(y, +2, -2, HEIGHT) * data->zoom) + data->shift_y;
	while (current_iter <= PERCISION)
	{
		z = vector_add(vector_square(z), c);
		if ((z.x * z.x) + (z.y * z.y) > MANDELBROT_MAX)
			return (current_iter);
		current_iter++;
	}
	return (current_iter * (-1));
}

void ft_create_image(void* param)
{
	uint32_t	y;
	uint32_t	i;
	int			iter;
	t_data		*data;

	data = get_data_ptr();
	i = 0;
	while (i < IMAGE_WIDTH)
	{
		y = 0;
		while (y < IMAGE_HEIGHT)
		{
			iter = is_in_mandelbrot(i, y);
			if (iter >= 0)
				data->color = ft_pixel(iter, 'p');
			else
				data->color = ft_pixel(iter, 'd');
			mlx_put_pixel(data->image, i, y, data->color);
			y++;
		}
		i++;
	}
}

void ft_hook_keyboard(void* param)
{
	t_data	*data;

	data = get_data_ptr();
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->shift_y += data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->shift_y -= data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->shift_x += data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->shift_x -= data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_I))
		printf("zoom:\t%f\nshift_x:\t%.15f\nshift_y:\t%.15f\n", data->zoom, data->shift_x, data->shift_y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_V))
		data->zoom = data->zoom * 1.20;
	if (mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->zoom = data->zoom * 0.8;
}

// void ft_hook_scroll(double xdelta, double ydelta, void* param)
// {
// 	t_data	*data;

// 	data = get_data_ptr();
// 	if (ydelta > 0) //zoom in
// 	{
// 		data->zoom = data->zoom * 1.20;
// 		set_center_to_mouse(&data);
// 	}
// 	else if (ydelta < 0) //zoom out
// 	{
// 		data->zoom = data->zoom * 0.8;
// //		set_center_to_mouse(&data);
// 	}
// }

void	set_center_to_mouse(t_data *data)
{
	int32_t	mouse_x;
	int32_t	mouse_y;

	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
}

int32_t	main(void)
{
	t_data	*data;

	data = get_data_ptr();
	data_init();
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
		return(EXIT_FAILURE);
	if (!(data->image = mlx_new_image(data->mlx, IMAGE_WIDTH, IMAGE_HEIGHT)))
	{
		mlx_close_window(data->mlx);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(data->mlx, ft_create_image, NULL);
	mlx_loop_hook(data->mlx, ft_hook_keyboard, NULL);
//	mlx_scroll_hook(data->mlx, ft_hook_scroll, NULL);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
