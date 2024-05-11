/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:54:52 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/11 19:10:24 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

/*
	Set julia values and z(0)
*/
static void	handle_fractals(t_coords *z, t_coords *c, t_data *data)
{
	if (!ft_strcmp(data->name, "julia"))
	{
		c->x = data->julia_i;
		c->y = data->julia_r;
	}
	else if (!ft_strcmp(data->name, "mandelbrot") || \
	!ft_strcmp(data->name, "burningship"))
	{
		c->x = z->x;
		c->y = z->y;
	}
}

/*
	Base formula	z = z^2 + c
	Julia			z(n+1) = z(n)^2 + c
		c is a constant set at the start. c is also a complex number.
		The result can either be a connected shape or an infinite
		amount of "dust" specs

	Mandelbrot		z(n+1) = z(n)^2 + z(0)
		A map of all connected Julia sets. If you pick a value from
		inside of the area of the mandelbrot set you will get a
		connected julia set

	Burning ship	z(n+1) = z^2 + z(0)
					z = (∣z(x)∣ + i∣z(y​)∣)
		a variation of these fractals with z(x) being the absolute
		value of z(x) being a real number and the absolute value z(y)
		being an complex number
*/
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
		if (!ft_strcmp(data->name, "burningship"))
		{
			temp.x = fabs(z.x * z.x - z.y * z.y + c.x);
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
