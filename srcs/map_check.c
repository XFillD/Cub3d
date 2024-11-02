/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:46 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/02 12:53:50 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_border(char *line)
{
	size_t	x;

	x = 0;
	while (x < ft_strlen(line) - 1)
	{
		if (line[x] != '1' && line[x] != ' ')
		{
			printf("Border error at col [%zu], its [%d]!\n", x, line[x]);
			return (FAIL);
		}
		x++;
	}
	return (SUCCESS);
}

int	check_borders(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map_h)
	{
		col = 0;
		while (game->map[row][col] == ' ')
			col++;
		if (row == 0 || row == game->map_h - 1)
		{
			if (check_border(game->map[row]))
				return (FAIL);
		}
		else
		{
			if (game->map[row][col] != '1')
				return (FAIL);
		}
		row++;
	}
	return (SUCCESS);
}

int	last_c_get(int row_n, int map_h, char *row)
{
	if (row_n == map_h - 1)
		return (ft_strlen(row) - 1);
	else
		return (ft_strlen(row) - 2);
}

int	space_check(t_game *game, int row, int col, int last_c)
{
	last_c = 0;
	while (row < game->map_h)
	{
		col = 0;
		while (game->map[row][col] == ' ')
			col++;
		last_c = last_c_get(row, game->map_h, game->map[row]);
		while (col < last_c)
		{
			if (game->map[row][col] == '0' && row != 0 && row != game->map_h
				- 1)
			{
				if (game->map[row + 1][col] == ' ')
					return (FAIL);
				if (game->map[row - 1][col] == ' ')
					return (FAIL);
			}
			col++;
		}
		if (game->map[row][last_c] != '1')
			return (FAIL);
		row++;
	}
	return (0);
}

int	map_check(t_game *game)
{
	if (check_borders(game) || space_check(game, 0, 0, 0))
		return (FAIL);
	check_player(game);
	return (SUCCESS);
}
