/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:15:31 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/09 15:17:09 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	check_empty_line(const char *line)
{
	int	x;
	int	char_flag;

	x = 0;
	char_flag = 0;
	while (line[x])
	{
		if (line[x] == '1' || line[x] == '0')
			char_flag = 1;
		x++;
	}
	if (char_flag == 0)
	{
		error("Empty line in the map!");
		exit(FAIL);
	}
}

// if it's part of the map - return 1
int	is_map_line(t_game *game, const char *line)
{
	int	x;

	x = 0;
	if (line[x] == ' ' || line[x] == '1' || line[x] == '0')
	{
		game->map_flag = 1;
		return (1);
	}
	else if (game->map_flag == 1)
		check_empty_line(line);
	return (0);
}

void	remove_newline(char *str)
{
	size_t	len;

	len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
}

void	remove_newline_all(t_game *game)
{
	remove_newline(game->design_config->east_texture);
	remove_newline(game->design_config->north_texture);
	remove_newline(game->design_config->south_texture);
	remove_newline(game->design_config->west_texture);
}
