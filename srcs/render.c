/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:22:41 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/02 13:31:04 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// render square
void	render_square_floor(t_mlx *mlx, int x, int y)
{
	int	i;
	int	j;
	int	s_square_m;

	s_square_m = (S_SQUARE * MINIMAP_SCALE);
	i = 0;
	while (i < s_square_m)
	{
		j = 0;
		while (j < s_square_m)
		{
			if (i == 0 || i == s_square_m - 1 || j == 0 || j == s_square_m - 1)
				mlx_put_pixel(mlx->img, (x * s_square_m) + i, (y * s_square_m)
					+ j, FLOOR_M_B_COLOUR);
			else
				mlx_put_pixel(mlx->img, (x * s_square_m) + i, (y * s_square_m)
					+ j, FLOOR_M_COLOUR);
			j++;
		}
		i++;
	}
}

// render square
void	render_square(t_mlx *mlx, int x, int y)
{
	int	i;
	int	j;
	int	s_square_m;

	s_square_m = (S_SQUARE * MINIMAP_SCALE);
	i = 0;
	while (i < s_square_m)
	{
		j = 0;
		while (j < s_square_m)
		{
			if (i == 0 || i == s_square_m - 1 || j == 0 || j == s_square_m - 1)
				mlx_put_pixel(mlx->img, (x * s_square_m) + i, (y * s_square_m)
					+ j, WALL_M_B_COLOUR);
			else
				mlx_put_pixel(mlx->img, (x * s_square_m) + i, (y * s_square_m)
					+ j, WALL_M_COLOUR);
			j++;
		}
		i++;
	}
}

// render square on the mini map
void	render_player(t_mlx *mlx, int colour, int start_x, int start_y)
{
	int	i;
	int	j;
	int	p_size;
	int	s_square_m;

	s_square_m = (S_SQUARE * MINIMAP_SCALE);
	p_size = (s_square_m / 2);
	start_x = (mlx->player->p_x * MINIMAP_SCALE) - (p_size / 2);
	start_y = (mlx->player->p_y * MINIMAP_SCALE) - (p_size / 2);
	i = 0;
	while (i < p_size)
	{
		j = 0;
		while (j < p_size)
		{
			mlx_put_pixel(mlx->img, start_x + j, start_y + i, colour);
			j++;
		}
		i++;
	}
}
