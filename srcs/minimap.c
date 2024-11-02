/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:56:52 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/02 13:23:04 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// visualise rays on the mini map
void	draw_ray_mini(t_mlx *mlx, float end_x, float end_y, int color)
{
	int		steps;
	float	x_increment;
	float	y_increment;
	float	x;
	float	y;

	steps = fmax(fabs(((end_x - mlx->player->p_x) * MINIMAP_SCALE)),
			fabs(((end_y - mlx->player->p_y) * MINIMAP_SCALE)));
	x_increment = ((end_x - mlx->player->p_x) * MINIMAP_SCALE) / steps;
	y_increment = ((end_y - mlx->player->p_y) * MINIMAP_SCALE) / steps;
	x = mlx->player->p_x * MINIMAP_SCALE;
	y = mlx->player->p_y * MINIMAP_SCALE;
	mlx->counter = 0;
	while (mlx->counter <= steps)
	{
		if (x >= 0 && x < S_W && y >= 0 && y < S_H)
			mlx_put_pixel(mlx->img, (int)x, (int)y, color);
		x += x_increment;
		y += y_increment;
		mlx->counter++;
	}
}

// render mini map - floor only
void	render_mini_map2(t_mlx *mlx)
{
	int	x;
	int	y;
	int	row_len;

	x = 0;
	row_len = 0;
	while (x < mlx->game->map_h)
	{
		y = 0;
		row_len = ft_strlen(mlx->game->map[x]);
		while (y < row_len)
		{
			if (mlx->game->map[x][y] == '0')
				render_square_floor(mlx, y, x);
			y++;
		}
		x++;
	}
}

// render mini map - walls only
void	render_mini_map(t_mlx *mlx)
{
	int	x;
	int	y;
	int	row_len;

	x = 0;
	row_len = 0;
	while (x < mlx->game->map_h)
	{
		y = 0;
		row_len = ft_strlen(mlx->game->map[x]);
		while (y < row_len)
		{
			if (mlx->game->map[x][y] == '1')
				render_square(mlx, y, x);
			y++;
		}
		x++;
	}
	render_player(mlx, 0xB99470FF, 0, 0);
}
