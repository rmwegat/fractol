/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:26:18 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/08 15:49:50 by rwegat           ###   ########.fr       */
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
# define IMAGE_HEIGHT 720
# define IMAGE_WIDTH 720
# define PERCISION 42
# define MANDELBROT_MAX 4

typedef struct s_coords
{
	double	x;
	double	y;
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
	t_mouse		*mouse;
	uint32_t	color;
	char		*name;
	int			current_iter;
	double		zoom;
	double		move_amount;
	double		shift_x;
	double		shift_y;
	double		julia_r;
	double		julia_i;
}	t_data;

//****		maths		****

double		scale_to_map(double unscaled, double old_max);
t_coords	vector_square(t_coords z);
t_coords	vector_add(t_coords z1, t_coords z2);

//****		utils		****

t_data		*get_data_ptr(void);
void		data_init(int argc, char **argv);
int32_t		data_mlx_init(void);
double		atod(char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//****		drawing		****

void		ft_create_image(void *param);
int			is_in_fractal(u_int32_t i, u_int32_t y);
int32_t		ft_pixel(int shift, char color);

#endif