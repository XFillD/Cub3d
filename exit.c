/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:14:53 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/27 17:27:10 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_exit_simple(t_game *game)
{
	int x; 
	x = 0;
	if (game->map)
		{
			while (game->map[x])
				free(game->map[x++]);
			free(game->map);
		}
	x = 0;
	if (game->buffer)
		{
			while (game->buffer[x])
				free(game->buffer[x++]);
			free(game->buffer);
		}
		free(game);
		
	exit(0);
}

// exit the game, free memory
void	ft_exit(t_mlx *mlx)
{
	int x = 0;
	if (mlx->game)
	{
		if (mlx->game->map)
		{
			while (mlx->game->map[x])
				free(mlx->game->map[x++]);
			free(mlx->game->map);
		}
		x=0;
		if (mlx->game->buffer)
		{
			while (mlx->game->buffer[x])
				free(mlx->game->buffer[x++]);
			free(mlx->game->buffer);
		}
		free(mlx->game);
	}
	if(mlx->player)
		free(mlx->player);
	if(mlx->ray)
		free(mlx->ray);
	if(mlx)
	{
		mlx_delete_image(mlx->p_mlx, mlx->img);
		mlx_close_window(mlx->p_mlx);
		mlx_terminate(mlx->p_mlx);
	}
	printf(COLOUR_GREEN "THANK YOU FOR PLAYING :3\n" COLOUR_RESET);
	exit(0);
}