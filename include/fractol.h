/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:26:18 by rwegat            #+#    #+#             */
/*   Updated: 2024/04/18 18:14:34 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define WIDTH 1024
# define HEIGHT 720
# define PERCISION 24
# define MANDELBROT_MAX 2

typedef struct s_coords
{
	double	x;
	double	y;
}	t_coords;

double scale_to_map(double unscaled, double new_min, \
double new_max, double old_max);
t_coords	vector_square(t_coords z);
t_coords	vector_add(t_coords z1, t_coords z2);

#endif 