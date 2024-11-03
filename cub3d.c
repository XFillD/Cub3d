/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:56:48 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/03 11:36:10 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

//main game loop
void game_loop(void *p_mlx)
{
	t_mlx *mlx; 

	mlx = p_mlx; 
	mlx_delete_image(mlx->p_mlx, mlx->img); 
	mlx->img = mlx_new_image(mlx->p_mlx, S_W, S_H);
	
	 

	hook(mlx, 0, 0); 
	ray_caster(mlx); 
	mlx_image_to_window(mlx->p_mlx, mlx->img, 0, 0); 
}

//init the player position in pixels and set angle and fov
void player_init(t_mlx *mlx)
{
    mlx->player->p_x = mlx->game->player_x * S_SQUARE + S_SQUARE / 2;
    mlx->player->p_y = mlx->game->player_y * S_SQUARE + S_SQUARE / 2;
    mlx->player->angle = M_PI; 
    mlx->player->fov = (FOV * M_PI) / 180; 
}

//init mlx and other structs 
void game_start(t_game *game)
{
    t_mlx mlx;

    mlx.game = game;

    mlx.player = ft_calloc(1, sizeof(t_player));
    mlx.p_mlx = mlx_init(S_W, S_H, "CUB3D", 0);
	mlx.ray = malloc(sizeof(t_ray) * S_W);

    player_init(&mlx);

	/*↓TESTING↓*/
    //printf("player_x [%d], player_y[%d], P_x[%d], P_y [%d], fov is [%f]\n", mlx.game->player_x, mlx.game->player_y, mlx.player->p_x, mlx.player->p_y, mlx.player->fov);
	/*↑TESTING↑*/

    mlx_loop_hook(mlx.p_mlx, &game_loop, &mlx);
    mlx_key_hook(mlx.p_mlx, &mlx_key, &mlx);
    mlx_loop(mlx.p_mlx);
}

//init game struct 
t_game *init_game()
{
    t_game *game = ft_calloc(1, sizeof(t_game)); 
	game->north_texture = NULL;
    game->south_texture= NULL;
    game->west_texture= NULL; 
    game->east_texture= NULL;
  	game->image= NULL;
    return(game); 
}

int main(int argc, char **argv)
{
	t_game *game; 
	(void)argc;
	(void)argv;

	if (argc != 2)
	{
		error("Invalid number of arguments!");
		exit(1);
	}

	game = init_game();

	map_read(game, argv[1]); 

	/*↓TESTING↓*/
	int x = 0; 
	while(game->map[x])
	{
		printf("%s",game->map[x]);
		x++; 
	}
	printf("\n");
	/*↑TESTING↑*/

	map_size(game);
	mini_map_size(game);
	find_player(game);
	game_start(game); 

    return (0);
}