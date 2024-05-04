/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 22:48:12 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/04 02:27:07 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void handle_fractals(t_coords *z, t_coords *c, t_data *data)
{
	if (!ft_strncmp(data->name, "julia", 6))
	{
		c->x = data->julia_i;
		c->y = data->julia_r;
	}
	else if (!ft_strncmp(data->name, "mandelbrot", 11))
	{
		c->x = z->x;
		c->y = z->y;
	}
}

int	is_in_fractal(u_int32_t i, u_int32_t y)
{
	t_coords	z;
	t_coords	c;
	int			current_iter;
	t_data		*data;

	data = get_data_ptr();
	current_iter = 0;

	z.x = (scale_to_map(i, -2, +2, WIDTH) * data->zoom) + data->shift_x;
	z.y = (scale_to_map(y, +2, -2, HEIGHT) * data->zoom) + data->shift_y;
	handle_fractals(&z, &c, data);
	while (current_iter <= PERCISION)
	{
		z = vector_add(vector_square(z), c);
		if ((z.x * z.x) + (z.y * z.y) > MANDELBROT_MAX)
			return (current_iter);
		current_iter++;
	}
	return (current_iter * (-1));
}
