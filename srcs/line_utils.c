/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:15:31 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/16 16:50:09 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	check_empty_line(const char *line, t_game *game)
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
		game->line_flag = 1;
}

// if it's part of the map - return 1
int	is_map_line(t_game *game, const char *line, size_t x, size_t count)
{
	if (game->map_flag == 0)
	{
		while (line[x])
		{
			if (line[x] == ' ' || line[x] == '1' || line[x] == '0'
				|| line[x] == 'N')
				count++;
			x++;
		}
		if (count > 0 && count == ft_strlen(line) - 1)
		{
			game->map_flag = 1;
			return (1);
		}
	}
	else
	{
		check_empty_line(line, game);
		if (line[x] == ' ' || line[x] == '1' || line[x] == '0')
			return (1);
	}
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

int	ft_strncmp2(char *s1, char *s2, size_t n)
{
	size_t	x;

	x = 0;
	while ((s1[x] || s2[x]) && x < n)
	{
		if ((unsigned char)s1[x] != (unsigned char)s2[x])
			return ((unsigned char)s1[x] - (unsigned char)s2[x]);
		x++;
	}
	return (0);
}
