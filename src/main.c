/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:32:36 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/11 01:36:27 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int32_t	ft_pixel(int iter, char color, t_color base_color)
{
	t_color	rgba;

	if (color == 'b')
	{
		rgba.r = (base_color.r + (iter * 14));
		rgba.g = (base_color.g + (iter * 6));
		rgba.b = (base_color.b + (iter * 10));
	}
	if (color == 'f' )
	{
		rgba.r = base_color.r + 0;
		rgba.g = base_color.g + 191;
		rgba.b = base_color.b + 255;
	}
	return (rgba.r << 24 | rgba.g << 16 | rgba.b << 8 | 255);
}

void	ft_create_image(void *param)
{
	uint32_t	y;
	uint32_t	i;
	int			iter;
	t_data		*data;

	data = get_data_ptr();
	(void)param;
	i = 0;
	while (i < IMAGE_WIDTH)
	{
		y = 0;
		while (y < IMAGE_HEIGHT)
		{
			iter = is_in_fractal(i, y);
			if (iter >= 0)
				data->color = ft_pixel(iter, 'b', data->base_color);
			else
				data->color = ft_pixel(iter, 'f', data->base_color);
			mlx_put_pixel(data->image, i, y, data->color);
			y++;
		}
		i++;
	}
}

void	put_usage(void)
{
	write(1, "ERROR INPUT\n", 13);
	write(1, "Usage:\n./fracol\tmandelbrot\n\t\tburningship\n\t\t", 43);
	write(1, "julia -0.8 0.165\n", 18);
	write (1, "try values between -2 and 2\n", 29);
	exit(EXIT_FAILURE);
}

static void	check_input(int argc, char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (len != 10 && len != 5 && len != 5)
		put_usage();
	if (ft_strcmp(argv[1], "mandelbrot") != 0 && \
		ft_strcmp(argv[1], "burningship") != 0 && \
		ft_strcmp(argv[1], "julia") != 0)
		put_usage();
	if (!ft_strcmp(argv[1], "mandelbrot") || \
		!ft_strcmp(argv[1], "burningship"))
		if (argc != 2)
			put_usage();
	if (!ft_strcmp(argv[1], "julia"))
		if (argc != 4)
			put_usage();
}

int32_t	main(int argc, char	**argv)
{
	t_data	*data;

	check_input(argc, argv);
	data = get_data_ptr();
	data_init(argc, argv);
	data_mlx_init();
	mlx_loop_hook(data->mlx, ft_create_image, NULL);
	mlx_loop_hook(data->mlx, ft_hook_keyboard, NULL);
	mlx_scroll_hook(data->mlx, ft_hook_scroll, NULL);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
