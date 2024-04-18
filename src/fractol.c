/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:36 by rwegat            #+#    #+#             */
/*   Updated: 2024/04/18 18:22:03 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fractol.h"

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool is_in_mandelbrot(u_int32_t i, u_int32_t y)
{
	t_coords	z;
	t_coords	c;
	int			current_perc;

	current_perc = 0;
	z.x = 0.0;
	z.y = 0.0;
	c.x = (scale_to_map(z.x, -2, +2, WIDTH));
	c.y = (scale_to_map(z.y, +2, -2, HEIGHT));
	while (current_perc <= PERCISION)
	{
		if ((z.x * z.x) + (z.y * z.y) > MANDELBROT_MAX)
		{
			return (true);
		}
		current_perc++;
	}
	return (false);
}

void ft_create_image(void* param)
{
	uint32_t	y;
	uint32_t	i;
	uint32_t	color;
	uint32_t	value;
	(void)param;
	i = 0;
	value = 0;
	while (i < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			if (is_in_mandelbrot(i, y))
				color = ft_pixel(0, 0, 0, 0);
			else
				color = ft_pixel(255, 255, 255, 255);
			mlx_put_pixel(image, i, y, color);
			y++;
			value++;
		}
		i++;
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int32_t main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH/2, HEIGHT/2)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_create_image, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// int	main(int argc, char **argv)
// {
// 	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10) || \
// 	argc == 4 && !ft_strncmp(argv[1], "julia", 5) )
// 	{
// 		fractol(argc, **argv);
// 	}
// 	else
// 	{
// 		ft_printf("USAGE:\n./fractol mandelbrot\nOR\n./fractol julia X Y\n");
// 		exit(EXIT_FAILURE);
// 	}
// }