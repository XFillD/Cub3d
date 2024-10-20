/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:23:34 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/19 17:43:10 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//better pixel put 
void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)	
{
	if (x < 0) 
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0) 
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color); 
}

// normalize the angle
float	angle_nor(float angle)	
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
