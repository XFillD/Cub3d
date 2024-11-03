/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:25:38 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/03 16:24:48 by yalechin         ###   ########.fr       */
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
	int	floor_color;
	int	ceiling_color;
	int	x;

	minimap_width = mlx->game->m_map_w;
	minimap_height = mlx->game->m_map_h;
	minimap_x = mlx->game->m_map_x;
	minimap_y = mlx->game->m_map_y;
	floor_color = (mlx->game->design_config->floor_color[0] << 24) | (mlx->game->design_config->floor_color[1] << 16) | (mlx->game->design_config->floor_color[2] << 8) | 0xFF;
	ceiling_color = (mlx->game->design_config->ceiling_color[0] << 24) | (mlx->game->design_config->ceiling_color[1] << 16) | (mlx->game->design_config->ceiling_color[2] << 8) | 0xFF;
	x = bottom_pix;
	while (x < S_H)
	{
		if (!(ray >= minimap_x && ray < minimap_x + minimap_width
				&& x >= minimap_y && x < minimap_y + minimap_height))
		{
			ft_pixel_put(mlx, ray, x, floor_color);
		}
		x++;
	}
	x = 0;
	while (x < top_pix)
	{
		if (!(ray >= minimap_x && ray < minimap_x + minimap_width
				&& x >= minimap_y && x < minimap_y + minimap_height))
		{
			ft_pixel_put(mlx, ray, x, ceiling_color);
		}
		x++;
	}
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_color_of_texture(int x, int y, mlx_texture_t *image)
{
	int	index;
	int	max;

	max = image->height * image->width * image->bytes_per_pixel;
	index = ((y * image->width) + x) * image->bytes_per_pixel;
	if (index >= max)
		return (0);
	return (get_rgba(image->pixels[index + 0], image->pixels[index + 1],
			image->pixels[index + 2], image->pixels[index + 3]));
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

void	get_texture_x(t_mlx *mlx, mlx_texture_t *image)
{
	// printf("mlx->was_hit_vertical %d\n", mlx->was_hit_vertical);
	// printf("mlx->ray[index].wall_hit_y %f\n", mlx->ray[index].wall_hit_y);
	// printf("mlx->ray[index].wall_hit_x %f\n", mlx->ray[index].wall_hit_x);
	// printf("index %d\n", index);
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

/*void	get_texture_y(t_mlx *mlx, mlx_texture_t *image, int top_pix,
		int bottom_pix, int wall_height)
{
	unsigned int	b;
	int				b;

	if (bottom_pix > 0
		&& bottom_pix < S_H)
		mlx->game->y_textures = (1 - (top_pix
					- bottom_pix)
				/ wall_height) * image->height;
}*/
int	reverse_bytes(int c)
{
	int b;
	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= S_H)
		return ;
	mlx_put_pixel(mlx->img, x, y, color); // put the pixel
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

void	draw_wall(t_mlx *mlx, int ray, int top_pix, int bottom_pix, int wall_h)
{
	int				minimap_width;
	int				minimap_height;
	int				minimap_x;
	int				minimap_y;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			x_textures;
	double			y_textures;
	double			factor;

	minimap_width = mlx->game->m_map_w;
	minimap_height = mlx->game->m_map_h;
	minimap_x = mlx->game->m_map_x;
	minimap_y = mlx->game->m_map_y;
	texture = get_texture(mlx, mlx->ray->wall);
	arr = (uint32_t *)texture->pixels;
	// Calculate y_textures increment to step through texture rows
	factor = (double)texture->height / wall_h;
	get_texture_x(mlx, texture);
	x_textures = mlx->game->x_textures;
	y_textures = (top_pix - (S_H / 2) + (wall_h / 2)) * factor;
	if (y_textures < 0)
		y_textures = 0;
	while (top_pix < bottom_pix)
	{
		if (!(ray >= minimap_x && ray < minimap_x + minimap_width
				&& top_pix >= minimap_y && top_pix < minimap_y
				+ minimap_height))
		{
			my_mlx_pixel_put(mlx, mlx->ray->index, top_pix,
				reverse_bytes(arr[(int)y_textures * texture->width
					+ (int)x_textures]));
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
	bottom_pix = (S_H / 2) + (wall_h / 2);
	top_pix = (S_H / 2) - (wall_h / 2);
	if (bottom_pix > S_H)
		bottom_pix = S_H;
	if (top_pix < 0)
		top_pix = 0;
	mlx->ray->index = ray;
	// get_texture_x(mlx, mlx->game->image);
	// get_texture_y(mlx, mlx->game->image, top_pix, bottom_pix, wall_h);
	draw_wall(mlx, ray, top_pix, bottom_pix, wall_h);
	draw_floor_ceiling(mlx, ray, top_pix, bottom_pix);
}
