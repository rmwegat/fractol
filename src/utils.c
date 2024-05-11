/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:22:42 by rwegat            #+#    #+#             */
/*   Updated: 2024/05/11 00:44:51 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_data	*get_data_ptr(void)
{
	static t_data	data;

	return (&data);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

double	extract_double(char *s)
{
	double	result;
	int		decimal_place;

	result = 0.0;
	decimal_place = 0;
	while (*s != '\0')
	{
		if (*s >= '0' && *s <= '9')
		{
			result = result * 10.0 + (*s - '0');
			if (decimal_place > 0)
				decimal_place *= 10;
		}
		else if (*s == '.')
			decimal_place = 1;
		s++;
	}
	if (decimal_place > 0)
		result /= decimal_place;
	return (result);
}

double	atod(char *s)
{
	double	result;
	int		decimal_place;
	int		is_negative;

	result = 0.0;
	decimal_place = 0;
	is_negative = 0;
	if (!*s)
		return (0);
	if (*s == '-')
	{
		is_negative = 1;
		s++;
	}
	result = extract_double(s);
	if (is_negative)
		result = -result;
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
