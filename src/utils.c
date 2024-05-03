/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwegat <rwegat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:52:11 by rwegat            #+#    #+#             */
/*   Updated: 2024/04/29 21:29:17 by rwegat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

t_data	*get_data_ptr(void)
{
	static t_data	data;

	return (&data);
}

void	data_init(void)
{
	t_data	*data;

	data = get_data_ptr();
	data->zoom = 1.0;
	data->move_amount = 0.5;
	data->shift_x = 0;
	data->shift_y = 0;
}