/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:46 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/16 17:48:02 by yalechin         ###   ########.fr       */
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

int	space_check(t_game *game, int r, int c, int last_c)
{
	last_c = 0;
	while (r < game->map_h)
	{
		c = 0;
		while (game->map[r][c] == ' ')
			c++;
		last_c = last_c_get(r, game->map_h, game->map[r]);
		while (c < last_c)
		{
			if (game->map[r][c] == '0' && r != 0 && r != game->map_h - 1)
			{
				if (!game->map[r + 1][c] || !game->map[r - 1][c])
					return (FAIL);
				if (game->map[r + 1][c] == ' ')
					return (FAIL);
				if (game->map[r - 1][c] == ' ')
					return (FAIL);
			}
			c++;
		}
		if (game->map[r][last_c] != '1')
			return (FAIL);
		r++;
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
