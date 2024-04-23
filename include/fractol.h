/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:26:18 by rwegat            #+#    #+#             */
/*   Updated: 2024/04/23 12:31:25 by rwegat           ###   ########.fr       */
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

# define WIDTH 720
# define HEIGHT 720
# define IMAGE_HEIGHT 1024
# define IMAGE_WIDTH 1024
# define PERCISION 42
# define MANDELBROT_MAX 2

typedef struct s_coords
{
	double	x;
	double	y;
	int		counter;
}	t_coords;

typedef struct s_color
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
}	t_color; 

typedef struct s_mouse
{
	int32_t		x;
	int32_t		y;
}	t_mouse;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	
	double		zoom;
}	t_img;

double scale_to_map(double unscaled, double new_min, \
double new_max, double old_max);
t_coords	vector_square(t_coords z);
t_coords	vector_add(t_coords z1, t_coords z2);

#endif