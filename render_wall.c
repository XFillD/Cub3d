/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:25:38 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/03 13:37:51 by fhauba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// draw the floor and the ceiling
void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pix, int bottom_pix)	
{
	int minimap_width = mlx->game->m_map_w;
	int minimap_height = mlx->game->m_map_h;
	int minimap_x =  mlx->game->m_map_x;
	int minimap_y = mlx->game->m_map_y;

//printf("floor color: %d, %d, %d\n", mlx->game->designConfig->floor_color[0], mlx->game->designConfig->floor_color[1], mlx->game->designConfig->floor_color[2]);
//printf("ceiling color: %d, %d, %d\n", mlx->designConfig->ceiling_color[0], mlx->designConfig->ceiling_color[1], mlx->designConfig->ceiling_color[2]);

	int floor_color = (mlx->game->designConfig->floor_color[0] << 24) |
                      (mlx->game->designConfig->floor_color[1] << 16) |
                      (mlx->game->designConfig->floor_color[2] << 8) | 0xFF;

    int ceiling_color = (mlx->game->designConfig->ceiling_color[0] << 24) |
                        (mlx->game->designConfig->ceiling_color[1] << 16) |
                        (mlx->game->designConfig->ceiling_color[2] << 8) | 0xFF;

	int		x;
	x = bottom_pix;
    while (x < S_H) {
        if (!(ray >= minimap_x && ray < minimap_x + minimap_width &&
              x >= minimap_y && x < minimap_y + minimap_height)) 
        {
           ft_pixel_put(mlx, ray, x, floor_color);  
        }
        x++;
    }
    x = 0;
    while (x < top_pix) {
        if (!(ray >= minimap_x && ray < minimap_x + minimap_width &&
              x >= minimap_y && x < minimap_y + minimap_height)) 
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
	return (get_rgba(
			image->pixels[index + 0],
			image->pixels[index + 1],
			image->pixels[index + 2],
			image->pixels[index + 3]));
}

// get the color of the wall
void	detect_texture(t_mlx *mlx)	
{
	mlx->ray->r_angle = angle_nor(mlx->ray->r_angle); // normalize the angle

	if(mlx->ray->direction == _NORTH)
	{
		mlx->game->image = mlx->game->north_texture;
	}
	else if(mlx->ray->direction == _SOUTH)
	{
		mlx->game->image = mlx->game->south_texture;
	}
	else if(mlx->ray->direction == _WEST)
	{
		mlx->game->image = mlx->game->west_texture;
	}
	else if(mlx->ray->direction == _EAST)
	{
		mlx->game->image = mlx->game->east_texture;
	}
}

//check wall collision
int check_wall(float x, float y, t_mlx *mlx)
{
    int map_x; 
    int map_y; 

    if(x < 0 || y < 0)
        return (0);
    map_x = floor(x / S_SQUARE); 
    map_y = floor(y / S_SQUARE);
    if(map_y >= mlx->game->map_h || map_x >= mlx->game->map_w)
        return(0); 
    if(mlx->game->map[map_y] && map_x <= (int)strlen(mlx->game->map[map_y]))
    {
        if(mlx->game->map[map_y][map_x] == '1')
            return(0); 
    }
    return(1);
}

void	get_texture_x(t_mlx *mlx, mlx_texture_t *image)
{
	if (mlx->game->was_hit_vertical == 1)
	{
		mlx->game->x_textures = fmod(mlx->ray->wall_hit_y, S_SQUARE)
			* (image->width / S_SQUARE);
	}
	else
	{
		if (mlx->ray->wall_hit_x >= 0
			&& mlx->ray->wall_hit_x < S_W)
			mlx->game->x_textures = fmod(mlx->ray->wall_hit_x, S_SQUARE)
				* (image->width / S_SQUARE);
	}
}

void	get_texture_y(t_mlx *mlx, mlx_texture_t *image, int top_pix, int bottom_pix, int wall_height)
{
	if (bottom_pix > 0
		&& bottom_pix < S_H)
		mlx->game->y_textures = (1 - (top_pix
					- bottom_pix)
				/ wall_height) * image->height;
}

void draw_wall(t_mlx *mlx, int ray, int top_pix, int bottom_pix)
{
    int minimap_width = mlx->game->m_map_w;
    int minimap_height = mlx->game->m_map_h;
    int minimap_x =  mlx->game->m_map_x;
    int minimap_y = mlx->game->m_map_y;
    
    // Calculate y_textures increment to step through texture rows
    double y_increment = (double)mlx->game->image->height / (bottom_pix - top_pix);
    double y_textures = 0;

    while (top_pix < bottom_pix) {
        if (!(ray >= minimap_x && ray < minimap_x + minimap_width &&
              top_pix >= minimap_y && top_pix < minimap_y + minimap_height)) 
        {
            int color = get_color_of_texture(mlx->game->x_textures, (int)y_textures, mlx->game->image);
            ft_pixel_put(mlx, ray, top_pix++, color);
            y_textures += y_increment; // Move to the next texture row
        } else {
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
	mlx->ray->distance *= cos(angle_nor(mlx->ray->r_angle - mlx->player->angle)); 
	wall_h = (S_SQUARE / mlx->ray->distance) * ((S_W / 2) / tan(mlx->player->fov / 2)); 
	bottom_pix = (S_H / 2) + (wall_h / 2); 
	top_pix = (S_H / 2) - (wall_h / 2); 
	if (bottom_pix > S_H) 
		bottom_pix = S_H;
	if (top_pix < 0) 
		top_pix = 0;

    detect_texture(mlx);
	get_texture_x(mlx, mlx->game->image);
	get_texture_y(mlx, mlx->game->image, top_pix, bottom_pix, wall_h);
	draw_wall(mlx, ray, top_pix, bottom_pix); 
	draw_floor_ceiling(mlx, ray, top_pix, bottom_pix);
}
