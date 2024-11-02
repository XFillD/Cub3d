/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:25:38 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/02 15:50:33 by fhauba           ###   ########.fr       */
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

printf("floor color: %d, %d, %d\n", mlx->designConfig->floor_color[0], mlx->designConfig->floor_color[1], mlx->designConfig->floor_color[2]);
printf("ceiling color: %d, %d, %d\n", mlx->designConfig->ceiling_color[0], mlx->designConfig->ceiling_color[1], mlx->designConfig->ceiling_color[2]);

	int floor_color = (mlx->designConfig->floor_color[0] << 24) |
                      (mlx->designConfig->floor_color[1] << 16) |
                      (mlx->designConfig->floor_color[2] << 8) | 0xFF;

    int ceiling_color = (mlx->designConfig->ceiling_color[0] << 24) |
                        (mlx->designConfig->ceiling_color[1] << 16) |
                        (mlx->designConfig->ceiling_color[2] << 8) | 0xFF;

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
void	detect_texture(t_mlx *mlx, int flag)	
{
        printf("Texture width: %d, height: %d\n", mlx->north_texture->width, mlx->north_texture->height);
        printf("Texture bytes per pixel: %d\n", mlx->north_texture->bytes_per_pixel);
        printf("Texture pixels: %p\n", mlx->north_texture->pixels);
        printf("Texture pixel 0: %d\n", mlx->north_texture->pixels[0]);
	mlx->ray->r_angle = angle_nor(mlx->ray->r_angle); // normalize the angle
	if (flag == 0)
	{
		if (mlx->ray->r_angle > M_PI / 2 && mlx->ray->r_angle < 3 * (M_PI / 2))
			mlx->image = mlx->west_texture; // west wall
		else
			mlx->image = mlx->east_texture; // east wall
	}
	else
	{
		if (mlx->ray->r_angle > 0 && mlx->ray->r_angle < M_PI)
			mlx->image = mlx->south_texture; // south wall
		else
			mlx->image = mlx->north_texture; // north wall
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

void	get_texture_x(t_mlx *mlx, int index, mlx_texture_t *image)
{
	printf("mlx->was_hit_vertical %d\n", mlx->was_hit_vertical);
	printf("mlx->ray[index].wall_hit_y %f\n", mlx->ray[index].wall_hit_y);
	printf("mlx->ray[index].wall_hit_x %f\n", mlx->ray[index].wall_hit_x);
	printf("index %d\n", index);
	if (mlx->was_hit_vertical == 1)
	{
		mlx->x_texures = fmod(mlx->ray[index].wall_hit_y, S_SQUARE)
			* (image->width / S_SQUARE);
	}
	else
	{
		if (mlx->ray[index].wall_hit_x >= 0
			&& mlx->ray[index].wall_hit_x < S_W)
			mlx->x_texures = fmod(mlx->ray[index].wall_hit_x, S_SQUARE)
				* (image->width / S_SQUARE);
	}
}

void	get_texture_y(t_mlx *mlx, mlx_texture_t *image, int top_pix, int bottom_pix, int wall_height)
{
	if (bottom_pix > 0
		&& bottom_pix < S_H)
		mlx->y_textures = (1 - (top_pix
					- bottom_pix)
				/ wall_height) * image->height;
}

// draw the wall
void	draw_wall(t_mlx *mlx, int ray, int top_pix, int bottom_pix)	
{
	int minimap_width = mlx->game->m_map_w;
	int minimap_height = mlx->game->m_map_h;

	int minimap_x =  mlx->game->m_map_x;
	int minimap_y = mlx->game->m_map_y;

	//color = 0xF5F5F5FF;
	//colour = get_colour(mlx, mlx->ray->wall);
	while (top_pix < bottom_pix) {
        if (!(ray >= minimap_x && ray < minimap_x + minimap_width &&
              top_pix >= minimap_y && top_pix < minimap_y + minimap_height)) 
        {
            ft_pixel_put(mlx, ray, top_pix++, get_color_of_texture(mlx->x_texures, mlx->y_textures, mlx->image));
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
		
	mlx->north_texture = mlx_load_png("textures/north.png");
    mlx->south_texture = mlx_load_png("textures/south.png");
    mlx->west_texture = mlx_load_png("textures/west.png");
    mlx->east_texture = mlx_load_png("textures/east.png");

    detect_texture(mlx, mlx->ray->wall);
	get_texture_x(mlx, ray, mlx->image);
	get_texture_y(mlx, mlx->image, top_pix, bottom_pix, wall_h);
	draw_wall(mlx, ray, top_pix, bottom_pix); 
	draw_floor_ceiling(mlx, ray, top_pix, bottom_pix);
}
