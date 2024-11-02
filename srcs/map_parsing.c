/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:03:47 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/02 13:36:29 by yalechin         ###   ########.fr       */
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

int	count_rows(t_game *game, char *file)
{
	char	*line;
	int		fd;
	int		rows;

	rows = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		error("MAP FILE ERROR");
		ft_exit_simple(game);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

// parse the file - store data in the structs
int	map_read(t_game *game, char *file, int x, int i)
{
	int	fd;
	int	rows;

	rows = count_rows(game, file);
	fd = open(file, O_RDONLY);
	game->buffer = (char **)malloc(((rows) + 1) * sizeof(char *));
	game->map = (char **)malloc(((rows) + 1) * sizeof(char *));
	if (!game->buffer || !game->map)
		ft_exit_simple(game);
	while (rows > 0)
	{
		game->buffer[i] = get_next_line(fd);
		if (is_map_line(game, game->buffer[i]))
		{
			game->map[x] = ft_strdup(game->buffer[i]);
			x++;
		}
		rows--;
		i++;
	}
	game->buffer[i] = NULL;
	game->map[x] = NULL;
	close(fd);
	return (SUCCESS);
}
