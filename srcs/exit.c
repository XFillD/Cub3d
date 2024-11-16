/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:14:53 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/16 13:37:38 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// exit when cross is pressed
void	close_game_callback(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_exit(mlx);
	exit(0);
}

// Function to check a condition and exit if needed
void	check_and_exit(int condition, t_game *game, const char *message)
{
	if (condition)
	{
		if (message)
			printf(COLOUR_RED "%s\n" COLOUR_RESET, message);
		ft_exit_simple(game);
	}
}

void	ft_exit_simple(t_game *game)
{
	int	x;

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
	free_textures(game);
	free_design_config(game->design_config);
	free(game);
	exit(0);
}

void	clear_game(t_game *game)
{
	int	x;

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
	free_textures(mlx->game);
	free_design_config(mlx->game->design_config);
	if (mlx->game)
		clear_game(mlx->game);
	if (mlx->player)
		free(mlx->player);
	if (mlx->ray)
		free(mlx->ray);
	mlx_delete_image(mlx->p_mlx, mlx->img);
	mlx_close_window(mlx->p_mlx);
	mlx_terminate(mlx->p_mlx);
	printf(COLOUR_GREEN "THANK YOU FOR PLAYING :3\n" COLOUR_RESET);
	exit(0);
}
