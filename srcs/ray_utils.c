/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:55:35 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/09 15:05:38 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

/*checks if a given angle is in a direction corresponding
to positive movement along the x-axis
or negative movement along the y-axis*/
int	angle_check(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

// check the intersection - adjust the direction of movement based on angle
int	check_inter(float angle, float *inter, float *step, int hrzntl)
{
	if (hrzntl)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += S_SQUARE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += S_SQUARE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}
