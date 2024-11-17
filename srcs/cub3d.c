/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:56:48 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/17 13:10:27 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// main game loop
void	game_loop(void *p_mlx)
{
	t_mlx	*mlx;

	mlx = p_mlx;
	mlx_delete_image(mlx->p_mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->p_mlx, S_W, S_H);
	hook(mlx, 0, 0);
	ray_caster(mlx, 0, 0, 0);
	mlx_image_to_window(mlx->p_mlx, mlx->img, 0, 0);
}

// init the player position in pixels and set angle and fov
void	player_init(t_mlx *mlx)
{
	mlx->player->p_x = mlx->game->player_x * S_SQUARE + S_SQUARE / 2;
	mlx->player->p_y = mlx->game->player_y * S_SQUARE + S_SQUARE / 2;
	mlx->player->angle = M_PI;
	mlx->player->fov = (FOV * M_PI) / 180;
}

// init mlx and other structs
void	game_start(t_game *game)
{
	t_mlx	mlx;

	mlx.game = game;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = ft_calloc(1, (sizeof(t_ray) * S_W));
	player_init(&mlx);
	mlx.p_mlx = mlx_init(S_W, S_H, "CUB3D", 0);
	if(!mlx.p_mlx)
		ft_exit(&mlx);
	mlx_loop_hook(mlx.p_mlx, &game_loop, &mlx);
	mlx_key_hook(mlx.p_mlx, &mlx_key, &mlx);
	mlx_close_hook(mlx.p_mlx, close_game_callback, &mlx);
	mlx_loop(mlx.p_mlx);
}

// init game struct
t_game	*init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->image = NULL;
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		error("Invalid number of arguments!");
		exit(1);
	}
	check_argv(argv[1]);
	file_check();
	game = init_game();
	if (map_read(game, argv[1], 0, 0))
	{
		error("MAP READ ERROR!");
		ft_exit_simple(game);
	}
	map_size(game);
	if (map_check(game))
	{
		error("MAP CHECK ERROR");
		ft_exit_simple(game);
	}
	mini_map_size(game);
	find_player(game);
	game_start(game);
	return (0);
}
