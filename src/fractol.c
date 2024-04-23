/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:36 by rwegat            #+#    #+#             */
/*   Updated: 2024/04/22 23:55:40 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fractol.h"

int32_t	ft_pixel(int shift, char color)
{
	t_rgba	rgba;
	if (color == 'p')
	{
		rgba.r = (180);
		rgba.g = (0 + shift * 10) % 256;
		rgba.b = (100);
	}
	if (color == 'd')
	{
		rgba.r = 75;
		rgba.g = 0;
		rgba.b = 130;
	}
	return (rgba.r << 24 | rgba.g << 16 | rgba.b << 8 | 255);
}

int	is_in_mandelbrot(u_int32_t i, u_int32_t y)
{
	t_coords	z;
	t_coords	c;
	int			current_iter;

	current_iter = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (scale_to_map(i, -2, +2, WIDTH));
	c.y = (scale_to_map(y, +2, -2, HEIGHT));
	while (current_iter <= PERCISION)
	{
		z = vector_add(vector_square(z), c);
		if ((z.x * z.x) + (z.y * z.y) > MANDELBROT_MAX)
			return (-1);
		current_iter++;
	}
	return (current_iter);
}

void ft_create_image(void* param)
{
	uint32_t	y;
	uint32_t	i;
	uint32_t	color;
	int			iteration;
	(void)param;
	i = 0;
	while (i < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			iteration = is_in_mandelbrot(i, y);
			if (iteration >= 0)
				color = ft_pixel(iteration, 'p');
			else
				color = ft_pixel(0, 'd');
			mlx_put_pixel(image, i, y, color);
			y++;
		}
		i++;
	}
}

void ft_hook_keyboard(void* param, mlx_image_t *image)
{
	mlx_t	*mlx;
	int		move_amount;

	mlx = param;
	move_amount = 5;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= move_amount;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) && \
		HEIGHT + image->instances[0].y + move_amount >= IMAGE_HEIGHT)
		image->instances[0].y += move_amount;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= move_amount;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += move_amount;
}

void ft_hook_scroll(double xdelta, double ydelta, void* param)
{
	if (ydelta > 0)
	{
		puts("Up");
	}
	else if (ydelta < 0)
	{
		puts("Down");
	}
	printf("%f\n", ydelta);
	printf("%f\n", xdelta);
}
int32_t main(void)
{
	mlx_t* mlx;
	static t_img	*img;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
		return(EXIT_FAILURE);
	if (!(img->image = mlx_new_image(mlx, IMAGE_WIDTH, IMAGE_HEIGHT)))
	{
		mlx_close_window(mlx);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, img->image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_create_image, mlx);
	mlx_loop_hook(mlx, ft_hook_keyboard, mlx);
	mlx_scroll_hook(mlx, ft_hook_scroll, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
