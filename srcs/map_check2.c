/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:27:51 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/02 12:53:53 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	check_argv(char *argv)
{
	int	x;

	x = ft_strlen(argv) - 4;
	if ((ft_strncmp(argv + x, ".cub", 4)) != 0)
	{
		error("Invalid map name!");
		exit(1);
	}
}

void	check_player(t_game *game)
{
	int	row;
	int	col;
	int	player;

	row = 0;
	col = 0;
	player = 0;
	while (row < game->map_h)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'N')
				player = 1;
			col++;
		}
		row++;
	}
	if (player == 0)
	{
		error("NO PLAYER FOUND!");
		ft_exit_simple(game);
	}
}
