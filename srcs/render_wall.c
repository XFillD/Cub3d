/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:25:38 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/02 13:29:09 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// draw the floor and the ceiling
void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pix, int bottom_pix)
{
	int	minimap_width;
	int	minimap_height;
	int	minimap_x;
	int	minimap_y;
	int	x;

	minimap_width = mlx->game->m_map_w;
	minimap_height = mlx->game->m_map_h;
	minimap_x = mlx->game->m_map_x;
	minimap_y = mlx->game->m_map_y;
	x = bottom_pix;
	while (x < S_H)
	{
		if (!(ray >= minimap_x && ray < minimap_x + minimap_width
				&& x >= minimap_y && x < minimap_y + minimap_height))
		{
			ft_pixel_put(mlx, ray, x, 0xB99470FF);
		}
		x++;
	}
	x = 0;
	while (x < top_pix)
	{
		if (!(ray >= minimap_x && ray < minimap_x + minimap_width
				&& x >= minimap_y && x < minimap_y + minimap_height))
		{
			ft_pixel_put(mlx, ray, x, 0x89CFF3FF);
		}
		x++;
	}
}

// get the color of the wall
int	get_colour(t_mlx *mlx, int flag)
{
	mlx->ray->r_angle = angle_nor(mlx->ray->r_angle);
	if (flag == 0)
	{
		if (mlx->ray->r_angle > M_PI / 2 && mlx->ray->r_angle < 3 * (M_PI / 2))
			return (0x7D7D7DFF);
		else
			return (0xE0E0E0FF);
	}
	else
	{
		if (mlx->ray->r_angle > 0 && mlx->ray->r_angle < M_PI)
			return (0x4B4B4BFF);
		else
			return (0x708090FF);
	}
}

// check wall collision
int	check_wall(float x, float y, t_mlx *mlx)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (0);
	map_x = floor(x / S_SQUARE);
	map_y = floor(y / S_SQUARE);
	if (map_y >= mlx->game->map_h || map_x >= mlx->game->map_w)
		return (0);
	if (mlx->game->map[map_y] && map_x <= (int)strlen(mlx->game->map[map_y]))
	{
		if (mlx->game->map[map_y][map_x] == '1')
			return (0);
	}
	return (1);
}

// draw the wall
void	draw_wall(t_mlx *mlx, int ray, int top_pix, int bottom_pix)
{
	int	colour;
	int	minimap_width;
	int	minimap_height;
	int	minimap_x;
	int	minimap_y;

	minimap_width = mlx->game->m_map_w;
	minimap_height = mlx->game->m_map_h;
	minimap_x = mlx->game->m_map_x;
	minimap_y = mlx->game->m_map_y;
	colour = get_colour(mlx, mlx->ray->wall);
	while (top_pix < bottom_pix)
	{
		if (!(ray >= minimap_x && ray < minimap_x + minimap_width
				&& top_pix >= minimap_y && top_pix < minimap_y
				+ minimap_height))
		{
			ft_pixel_put(mlx, ray, top_pix++, colour);
		}
		else
		{
			top_pix++;
		}
	}
}

// render the wall
void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	bottom_pix;
	double	top_pix;

	mlx->ray->distance *= cos(angle_nor(mlx->ray->r_angle
				- mlx->player->angle));
	wall_h = (S_SQUARE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->player->fov
				/ 2));
	bottom_pix = (S_H / 2) + (wall_h / 2);
	top_pix = (S_H / 2) - (wall_h / 2);
	if (bottom_pix > S_H)
		bottom_pix = S_H;
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(mlx, ray, top_pix, bottom_pix);
	draw_floor_ceiling(mlx, ray, top_pix, bottom_pix);
}
