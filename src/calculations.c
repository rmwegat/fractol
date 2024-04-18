/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:39:40 by rwegat            #+#    #+#             */
/*   Updated: 2024/04/18 18:09:55 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

double	scale_to_map(double unscaled, double new_min, \
double new_max, double old_max)
{
	return ((new_max - new_min) *(unscaled - 0) / old_max + new_min);
}

t_coords	vector_add(t_coords z1, t_coords z2)
{
	t_coords	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_coords	vector_square(t_coords z)
{
	t_coords	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}