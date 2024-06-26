/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:02:02 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/11 19:15:44 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	data_init(int argc, char **argv)
{
	t_data	*data;

	data = get_data_ptr();
	data->zoom = 1.0;
	data->move_amount = 0.5;
	data->shift_x = 0;
	data->shift_y = 0;
	data->base_color.r = 0;
	data->base_color.g = 0;
	data->base_color.b = 0;
	if ((argc == 2 && !ft_strcmp(argv[1], "mandelbrot")) \
		|| (argc == 4 && !ft_strcmp(argv[1], "julia")) \
		|| (argc == 2 && !ft_strcmp(argv[1], "burningship")))
	{
		data->name = argv[1];
		if (!argv[2] || !argv[3])
			return ;
		data->julia_i = atod(argv[2]);
		data->julia_r = atod(argv[3]);
		if ((data->julia_i > 2.0 || data->julia_i < -2.0) || \
			(data->julia_r > 2.0 || data->julia_r < -2.0))
		{
			write(1, "4", 1);
			put_usage();
		}
	}
}

int32_t	data_mlx_init(void)
{
	t_data	*data;

	data = get_data_ptr();
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->image = mlx_new_image(data->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!data->image)
	{
		mlx_close_window(data->mlx);
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		return (EXIT_FAILURE);
	}
	return (0);
}
