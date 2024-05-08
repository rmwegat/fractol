/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:54:52 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/08 15:50:35 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static void	handle_fractals(t_coords *z, t_coords *c, t_data *data)
{
	if (!ft_strncmp(data->name, "julia", 6))
	{
		c->x = data->julia_i;
		c->y = data->julia_r;
	}
	else if (!ft_strncmp(data->name, "mandelbrot", 11) || \
	!ft_strncmp(data->name, "burningship", 12))
	{
		c->x = z->x;
		c->y = z->y;
	}
}

int	is_in_fractal(u_int32_t i, u_int32_t y)
{
	t_coords	z;
	t_coords	c;
	t_coords	temp;
	t_data		*data;

	data = get_data_ptr();
	data->current_iter = 0;
	z.x = (scale_to_map(i, WIDTH) * data->zoom) + data->shift_x;
	z.y = (scale_to_map(y, HEIGHT) * data->zoom) + data->shift_y;
	handle_fractals(&z, &c, data);
	while (++data->current_iter <= PERCISION)
	{
		if (!ft_strncmp(data->name, "burningship", 12))
		{
			temp.x = z.x * z.x - z.y * z.y + c.x;
			temp.y = fabs(2 * z.x * z.y) + c.y;
			z.y = temp.y;
			z.x = temp.x;
		}
		else
			z = vector_add(vector_square(z), c);
		if ((z.x * z.x) + (z.y * z.y) > MANDELBROT_MAX)
			return (data->current_iter);
	}
	return (data->current_iter * (-1));
}
