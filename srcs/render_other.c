/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:42:56 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/17 12:58:12 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

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
	if (mlx->game->map[map_y] && map_x <= (int)ft_strlen(mlx->game->map[map_y]))
	{
		if (mlx->game->map[map_y][map_x] == '1')
			return (0);
	}
	return (1);
}

void	draw_floor(t_mlx *mlx, int ray, int bottom_pix)
{
	int	minimap_x;
	int	minimap_y;
	int	floor_color;
	int	x;

	minimap_x = mlx->game->m_map_x;
	minimap_y = mlx->game->m_map_y;
	floor_color = (mlx->game->design_config->floor_color[0] << 24) \
	| (mlx->game->design_config->floor_color[1] << 16) \
	| (mlx->game->design_config->floor_color[2] << 8) | 0xFF;
	x = bottom_pix;
	while (x < S_H)
	{
		if (!(ray >= minimap_x && ray < minimap_x + mlx->game->m_map_w
				&& x >= minimap_y && x < minimap_y + mlx->game->m_map_h))
		{
			ft_pixel_put(mlx, ray, x, floor_color);
		}
		x++;
	}
}

// draw the floor and the ceiling
void	draw_ceiling(t_mlx *mlx, int ray, int top_pix)
{
	int	minimap_x;
	int	minimap_y;
	int	ceiling_color;
	int	x;

	minimap_x = mlx->game->m_map_x;
	minimap_y = mlx->game->m_map_y;
	ceiling_color = (mlx->game->design_config->ceiling_color[0] << 24) \
	| (mlx->game->design_config->ceiling_color[1] << 16) \
	| (mlx->game->design_config->ceiling_color[2] << 8) | 0xFF;
	x = 0;
	while (x < top_pix)
	{
		if (!(ray >= minimap_x && ray < minimap_x + mlx->game->m_map_w
				&& x >= minimap_y && x < minimap_y + mlx->game->m_map_h))
		{
			ft_pixel_put(mlx, ray, x, ceiling_color);
		}
		x++;
	}
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pix, int bottom_pix)
{
	draw_ceiling(mlx, ray, top_pix);
	draw_floor(mlx, ray, bottom_pix);
}
