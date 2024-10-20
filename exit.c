/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:14:53 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/19 16:18:06 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//exit the game, free memory
void	ft_exit(t_mlx *mlx) 		
{
	int	x = 0;
	while (mlx->game->map[x])
		free(mlx->game->map[x++]); 
	free(mlx->game->map); 
	free(mlx->game); 
	free(mlx->player); 
	free(mlx->ray); 
	mlx_delete_image(mlx->p_mlx, mlx->img); 
	mlx_close_window(mlx->p_mlx); 
	mlx_terminate(mlx->p_mlx);
	printf(COLOUR_GREEN"THANK YOU FOR PLAYING :3\n"COLOUR_RESET); 
	exit(0); 
}