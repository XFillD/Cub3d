/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:57:40 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/03 15:12:16 by fhauba           ###   ########.fr       */
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

void setFlag(double inter_h, double inter_v, t_mlx *mlx)
{
    if(inter_v < inter_h)
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
		
		if(mlx->ray->interh < mlx->ray->interv)
        {
            mlx->ray->wall_hit_x = mlx->ray->hx;
            mlx->ray->wall_hit_y = mlx->ray->hy;
        }
        else 
        {
            mlx->ray->wall_hit_x = mlx->ray->vx;
            mlx->ray->wall_hit_y = mlx->ray->vy;
        }

		mlx->ray->interh = inter_h;
		mlx->ray->interv = inter_v;
		
		if (inter_v <= inter_h)
			mlx->ray->distance = inter_v;
		else
		{
			mlx->ray->distance = inter_h;
			mlx->ray->wall = 1;
		}
		setFlag(inter_h, inter_v, mlx);
		if (inter_v < inter_h)
			draw_ray_mini(mlx, mlx->ray->vx, mlx->ray->vy, 0x00FF00FF);
		else
			draw_ray_mini(mlx, mlx->ray->hx, mlx->ray->hy, 0xFF0000FF);
		render_wall(mlx, ray);
		ray++;
		mlx->ray->r_angle += (mlx->player->fov / S_W);
	}
	render_mini_map(mlx);
}
