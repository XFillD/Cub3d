/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:13:14 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/03 13:30:31 by fhauba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

//release key - flag reset
void	ft_release(mlx_key_data_t keydata, t_mlx *mlx)	
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->player->m_h = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->player->m_h = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->player->m_v = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->player->m_v = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->player->rot = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->player->rot = 0;
}

//key press flag set 
void mlx_key(mlx_key_data_t keydata, void *ml)	
{
	t_mlx	*mlx;


	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) 
		ft_exit(mlx);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) 
		mlx->player->m_h = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) 
		mlx->player->m_h = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) 
		mlx->player->m_v = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) 
        mlx->player->m_v = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) 
		mlx->player->rot = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) 
		mlx->player->rot = 1;
	ft_release(keydata, mlx); 
}

//set rotation angle 
void rotate_player(t_mlx *mlx, int x)
{
	if(x == 1)
	{
		mlx->player->angle += ROTATION_SPEED; 
		if(mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED; 
		if(mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

//update player position 
void move_player(t_mlx *mlx, double move_v, double move_h)
{

    int new_x = roundf(mlx->player->p_x + move_v);  
    int new_y = roundf(mlx->player->p_y + move_h);

    int map_x = (new_x / S_SQUARE);
    int map_y = (new_y / S_SQUARE);

    if (mlx->game->map[map_y][map_x] != '1' && \
	(mlx->game->map[map_y][mlx->player->p_x / S_SQUARE] != '1' && \
	mlx->game->map[mlx->player->p_y / S_SQUARE][map_x] != '1'))  
    {
        mlx->player->p_x = new_x;
        mlx->player->p_y = new_y;
    }
    
}

//move the player 
void hook(t_mlx *mlx, double move_v, double move_h)
{

	if(mlx->player->rot == 1)
		rotate_player(mlx, 1);
	if(mlx->player->rot == -1)
		rotate_player(mlx, 0);
    if (mlx->player->m_h == 1) {  
        move_v = -sin(mlx->player->angle) * PLAYER_SPEED;  
        move_h = cos(mlx->player->angle) * PLAYER_SPEED;  
    }
    if (mlx->player->m_h == -1) { 
        move_v = sin(mlx->player->angle) * PLAYER_SPEED; 
        move_h = -cos(mlx->player->angle) * PLAYER_SPEED; 
    }
    if (mlx->player->m_v == 1) {  
        move_v = cos(mlx->player->angle) * PLAYER_SPEED; 
        move_h = sin(mlx->player->angle) * PLAYER_SPEED;  
    }
    if (mlx->player->m_v == -1) { 
        move_v = -cos(mlx->player->angle) * PLAYER_SPEED; 
        move_h = -sin(mlx->player->angle) * PLAYER_SPEED; 
    }
	move_player(mlx, move_v, move_h);
}