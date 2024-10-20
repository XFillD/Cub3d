/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:56:52 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/20 13:19:06 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

//draw the direction line - helper function 
void render_player_direction_mini(t_mlx *mlx)
{
    int start_x = mlx->player->p_x * MINIMAP_SCALE; 
    int start_y = mlx->player->p_y * MINIMAP_SCALE;

    int mini_w = (S_W * S_SQUARE) * MINIMAP_SCALE;
     int mini_h = (S_H * S_SQUARE) * MINIMAP_SCALE;
    
    int line_length = 15;  
    
    int end_x = start_x + cos(mlx->player->angle) * line_length;
    int end_y = start_y + sin(mlx->player->angle) * line_length;


    int i = 0;

    while (i <= line_length) 
    {  
        int x = start_x + (end_x - start_x) * i / line_length;
        int y = start_y + (end_y - start_y) * i / line_length;

        if (x >= 0 && x < mini_w && y >= 0 && y < mini_h) {
            mlx_put_pixel(mlx->img, x, y, 0xFF0000FF); 
        }

        i++;  
    }
}

//render square
void render_square(t_mlx *mlx, int x, int y, int colour, int border_colour)
{
    int i = 0;
    int j;

    while (i < S_SQUARE_M) {
        j = 0;
        while (j < S_SQUARE_M) {
            if (i == 0 || i == S_SQUARE_M - 1 || j == 0 || j == S_SQUARE_M - 1)
                mlx_put_pixel(mlx->img, (x * S_SQUARE_M) + i, (y * S_SQUARE_M) + j, border_colour);
            else  
                mlx_put_pixel(mlx->img, (x * S_SQUARE_M) + i, (y * S_SQUARE_M) + j, colour);
            
            j++;  
        }
        i++;  
    }
}

//render square on the mini map
void render_player(t_mlx *mlx, int colour)
{
    int i, j;
    int start_x = (mlx->player->p_x * MINIMAP_SCALE) - (P_SIZE / 2);
    int start_y = (mlx->player->p_y * MINIMAP_SCALE) - (P_SIZE / 2);


    i = 0;

    while (i < P_SIZE) {
        j = 0;
        while (j < P_SIZE) {
            mlx_put_pixel(mlx->img, start_x + j, start_y + i, colour);
            j++;  
        }
        i++; 
    }
}

//visualise rays on the mini map 
void draw_ray_mini(t_mlx *mlx, float start_x, float start_y, float end_x, float end_y, int color)
{
   
    float scale = MINIMAP_SCALE; 
   
    float dx = (end_x - start_x) * scale;
    float dy = (end_y - start_y) * scale;

    int steps = fmax(fabs(dx), fabs(dy));
    float x_increment = dx / steps;
    float y_increment = dy / steps;

    float x = start_x * scale; 
    float y = start_y * scale; 

    int i = 0;  

    while (i <= steps)
    {
        if (x >= 0 && x < S_W && y >= 0 && y < S_H)
            mlx_put_pixel(mlx->img, (int)x, (int)y, color); 

        x += x_increment;
        y += y_increment;
        
        i++;  
    }
}

//render mini map - floor only 
void render_mini_map2(t_mlx *mlx)
{
    int x = 0;
    int y;
    int row_len; 

    row_len = 0; 

    while (x < mlx->game->map_h) {
        y = 0;
        row_len = ft_strlen(mlx->game->map[x]);
        while (y < row_len) {
        if (mlx->game->map[x][y] == '0') 
            render_square(mlx, y, x, 0x000000, 0xFF0000FF);
        y++;  // Increment y in the inner loop
    }
    x++;  // Increment x in the outer loop
}

}

//render mini map - walls only 
void render_mini_map(t_mlx *mlx)
{
    int x = 0;
    int y;
    int row_len; 

    row_len = 0; 

    while (x < mlx->game->map_h) {
        y = 0;
        row_len = ft_strlen(mlx->game->map[x]);
        while (y < row_len) {
        if (mlx->game->map[x][y] == '1')  
            render_square(mlx, y, x, 0xFFFFFF, 0xFF0000FF); 
        y++;  // Increment y inside the inner while loop
    }
    x++;  // Increment x inside the outer while loop
}

    render_player(mlx, 0xB99470FF); 
    //render_player_direction_mini(mlx);
}

