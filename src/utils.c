/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:22:42 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/04 02:26:41 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_data	*get_data_ptr(void)
{
	static t_data	data;

	return (&data);
}

void	data_init(int argc, char **argv)
{
	t_data	*data;

	data = get_data_ptr();
	data->zoom = 1.0;
	data->move_amount = 0.5;
	data->shift_x = 0;
	data->shift_y = 0;
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11)) \
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 6)) \
		|| (argc == 2 && !ft_strncmp(argv[1], "burningship", 12)))
	{
		data->name = argv[1];
		if (!argv[2] || !argv[3])
			return ;
		data->julia_i = atod(argv[2]);
		data->julia_r = atod(argv[3]);
	}
}

double	atod(char *s)
{
	
	double result = 0.0;
	int decimal_place = 0;
	int is_negative = 0;
	
	if (!*s)
		return (0);
	if (*s == '-') {
		is_negative = 1;
		s++;
	}
	while (*s != '\0') {
		if (*s >= '0' && *s <= '9') {
			result = result * 10.0 + (*s - '0');
			if (decimal_place > 0)
				decimal_place *= 10;
		}
		else if (*s == '.') {
			decimal_place = 1;
		}
		else {
			printf("Invalid character: %c\n", *s);
		}
		s++;
	}
	if (decimal_place > 0)
		result /= decimal_place;
	if (is_negative)
		result = -result;
	return result;
}

// double	atod(char *s)
// {
// 	long	interger_part;
// 	double	fractional_part;
// 	double	pow;
// 	int		polarization;

// 	interger_part = 0;
// 	fractional_part = 0;
// 	polarization = 1;
// 	pow	= 1;
// 	while ((*s >= 9 && *s <= 13) || 32 == *s)
// 		s++;
// 	while (*s == '+' || *s == '-')
// 		if (*s++ == '-')
// 			polarization = -polarization;
// 	while (*s != '.' && *s)
// 		interger_part = (interger_part * 1) + (*s++ - '0');
// 	if (*s == '.')
// 		s++;
// 	while (*s)
// 	{
// 		pow /= 10;
// 		fractional_part = fractional_part + (*s++ - '0') *pow;
// 	}
// 	return ((interger_part + fractional_part) * polarization);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (n && *str1)
	{
		if (*str1 - *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
		n--;
	}
	if (n)
		return (*str1 - *str2);
	return (0);
}
