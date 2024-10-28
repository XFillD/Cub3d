/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yana <yana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:14:53 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/28 17:16:23 by yana             ###   ########.fr       */
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

void clear_game(t_game *game)
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
}

// exit the game, free memory
void	ft_exit(t_mlx *mlx)
{
	if (mlx->game)
		clear_game(mlx->game);
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