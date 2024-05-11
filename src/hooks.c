/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 21:25:50 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/10 23:21:30 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	change_color(void)
{
	t_data	*data;

	data = get_data_ptr();
	data->base_color.r += 5 % 150;
	data->base_color.g += 7 % 150;
	data->base_color.b += 10 % 150;
}

void	reset_color(void)
{
	t_data	*data;

	data = get_data_ptr();
	data->base_color.r = 0;
	data->base_color.g = 0;
	data->base_color.b = 0;
}

void	ft_hook_keyboard(void *param)
{
	t_data	*data;

	data = get_data_ptr();
	(void)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->shift_y += data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->shift_y -= data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->shift_x += data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->shift_x -= data->move_amount * data->zoom;
	if (mlx_is_key_down(data->mlx, MLX_KEY_C))
		change_color();
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		reset_color();
}

void	ft_hook_scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = get_data_ptr();
	(void)param;
	(void)xdelta;
	if (ydelta > 0)
		data->zoom = data->zoom * 1.20;
	else if (ydelta < 0)
		data->zoom = data->zoom * 0.8;
}
