/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:52:51 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/20 12:35:51 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//reculculate the mini map size - assign to struct 
void mini_map_size(t_game *game)
{
	game->m_map_w = S_SQUARE_M * game->map_w;
	game->m_map_h = S_SQUARE_M * game->map_h;
	game->m_map_x = 0;
	game->m_map_y = 0;

}

//get the map size - store the value in the struct
void map_size(t_game *game)
{
	int x; 
	int y;
	int len; 

	x = 0;
	y = 0;
	len = 0; 
	
	while(game->map[x])
	{
		y = 0;
		while(game->map[x][y])
			y++; 
		if(y > len)
			len = y; 
		x++;
	}

	game->map_w = len-1;
	game->map_h = x;
}


//find the player position - store data in the struct
void find_player(t_game* game)
{
	int x; 
	int y;
	x = 0;
	y = 0;
	
	while(game->map[x])
	{
		y = 0;
		while(game->map[x][y])
		{
			if(game->map[x][y] == 'N')
			{
				game->player_x = y;
				game->player_y = x;
			}
			y++;
		}
		x++;
	}

}