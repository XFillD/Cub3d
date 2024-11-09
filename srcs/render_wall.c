/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:25:38 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/09 14:54:13 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	get_texture_x(t_mlx *mlx, mlx_texture_t *image)
{
	if (mlx->game->was_hit_vertical == 1)
	{
		mlx->game->x_textures = fmod(mlx->ray->wall_hit_y, S_SQUARE)
			* (image->width / S_SQUARE);
	}
	else
	{
		if (mlx->ray->wall_hit_x >= 0 && mlx->ray->wall_hit_x < S_W)
			mlx->game->x_textures = fmod(mlx->ray->wall_hit_x, S_SQUARE)
				* (image->width / S_SQUARE);
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
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

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->r_angle = angle_nor(mlx->ray->r_angle);
	if (flag == 0)
	{
		if (mlx->ray->r_angle > M_PI / 2 && mlx->ray->r_angle < 3 * (M_PI / 2))
			return (mlx->game->east_texture);
		else
			return (mlx->game->west_texture);
	}
	else
	{
		if (mlx->ray->r_angle > 0 && mlx->ray->r_angle < M_PI)
			return (mlx->game->south_texture);
		else
			return (mlx->game->north_texture);
	}
}

void	draw_wall(t_mlx *mlx, int ray, int top_pix, int bottom_pix)
{
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			y_textures;
	double			factor;

	texture = get_texture(mlx, mlx->ray->wall);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / mlx->ray->wall_h;
	get_texture_x(mlx, texture);
	y_textures = (top_pix - (S_H / 2) + (mlx->ray->wall_h / 2)) * factor;
	if (y_textures < 0)
		y_textures = 0;
	while (top_pix < bottom_pix)
	{
		if (!(ray >= mlx->game->m_map_x && ray < mlx->game->m_map_x
				+ mlx->game->m_map_w && top_pix >= mlx->game->m_map_y
				&& top_pix < mlx->game->m_map_y + mlx->game->m_map_h))
		{
			my_mlx_pixel_put(mlx, mlx->ray->index, top_pix,
				bytes_reverse(arr[(int)y_textures * texture->width
					+ (int)mlx->game->x_textures]));
		}
		top_pix++;
		y_textures += factor;
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
	mlx->ray->wall_h = wall_h;
	bottom_pix = (S_H / 2) + (wall_h / 2);
	top_pix = (S_H / 2) - (wall_h / 2);
	if (bottom_pix > S_H)
		bottom_pix = S_H;
	if (top_pix < 0)
		top_pix = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, ray, top_pix, bottom_pix);
	draw_floor_ceiling(mlx, ray, top_pix, bottom_pix);
}
