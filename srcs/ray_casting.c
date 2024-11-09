/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:57:40 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/09 15:00:42 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// calculate vetical intersection
float	vertical(t_mlx *mlx, float angle)
{
	float	vx;
	float	vy;
	float	x_step;
	float	y_step;
	int		pxl;

	x_step = S_SQUARE;
	y_step = S_SQUARE * tan(angle);
	vx = floor(mlx->player->p_x / S_SQUARE) * S_SQUARE;
	pxl = check_inter(angle, &vx, &x_step, 0);
	vy = mlx->player->p_y + (vx - mlx->player->p_x) * tan(angle);
	if ((angle_check(angle, 'x') && y_step < 0) || (!angle_check(angle, 'x')
			&& y_step > 0))
		y_step *= -1;
	while (check_wall(vx - pxl, vy, mlx))
	{
		vx += x_step;
		vy += y_step;
	}
	mlx->ray->vx = vx;
	mlx->ray->vy = vy;
	return (sqrt(pow(vx - mlx->player->p_x, 2) + pow(vy - mlx->player->p_y,
				2)));
}

// calculate horizontal intersection
float	horizontal(t_mlx *mlx, float angle)
{
	float	hx;
	float	hy;
	float	x_step;
	float	y_step;
	int		pxl;

	y_step = S_SQUARE;
	x_step = S_SQUARE / tan(angle);
	hy = floor(mlx->player->p_y / S_SQUARE) * S_SQUARE;
	pxl = check_inter(angle, &hy, &y_step, 1);
	hx = mlx->player->p_x + (hy - mlx->player->p_y) / tan(angle);
	if ((angle_check(angle, 'y') && x_step > 0) || (!angle_check(angle, 'y')
			&& x_step < 0))
		x_step *= -1;
	while (check_wall(hx, hy - pxl, mlx))
	{
		hx += x_step;
		hy += y_step;
	}
	mlx->ray->hx = hx;
	mlx->ray->hy = hy;
	return (sqrt(pow(hx - mlx->player->p_x, 2) + pow(hy - mlx->player->p_y,
				2)));
}

void	set_flag(double inter_h, double inter_v, t_mlx *mlx)
{
	if (inter_v < inter_h)
	{
		mlx->game->was_hit_vertical = 1;
		if (cos(mlx->ray->r_angle) > 0)
			mlx->ray->direction = _EAST;
		else
			mlx->ray->direction = _WEST;
	}
	else
	{
		mlx->game->was_hit_vertical = 0;
		if (sin(mlx->ray->r_angle) > 0)
			mlx->ray->direction = _SOUTH;
		else
			mlx->ray->direction = _NORTH;
	}
}

void	set_wall_hit(double inter_h, double inter_v, t_mlx *mlx)
{
	if (inter_h < inter_v)
	{
		mlx->ray->wall_hit_x = mlx->ray->hx;
		mlx->ray->wall_hit_y = mlx->ray->hy;
	}
	else
	{
		mlx->ray->wall_hit_x = mlx->ray->vx;
		mlx->ray->wall_hit_y = mlx->ray->vy;
	}
}

// main ray calculation
void	ray_caster(t_mlx *mlx, double inter_h, double inter_v, int ray)
{
	mlx->ray->r_angle = mlx->player->angle - (mlx->player->fov / 2);
	render_mini_map2(mlx);
	while (ray < S_W)
	{
		mlx->ray->wall = 0;
		inter_h = horizontal(mlx, angle_nor(mlx->ray->r_angle));
		inter_v = vertical(mlx, angle_nor(mlx->ray->r_angle));
		set_wall_hit(inter_h, inter_v, mlx);
		if (inter_v <= inter_h)
			mlx->ray->distance = inter_v;
		else
		{
			mlx->ray->distance = inter_h;
			mlx->ray->wall = 1;
		}
		set_flag(inter_h, inter_v, mlx);
		if (inter_v < inter_h)
			draw_ray_mini(mlx, mlx->ray->vx, mlx->ray->vy, 0xFFFFC0CB);
		else
			draw_ray_mini(mlx, mlx->ray->hx, mlx->ray->hy, 0xFFFFEFD5);
		render_wall(mlx, ray);
		ray++;
		mlx->ray->r_angle += (mlx->player->fov / S_W);
	}
	render_mini_map(mlx);
}
