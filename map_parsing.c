/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:03:47 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/27 17:45:49 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_empty_line(char *line)
{
	int x = 0;
	int char_flag; 
	char_flag = 0;
	while(line[x])
	{
		if(line [x] == '1' || line[x] == '0')
				char_flag = 1;
		x++;
	}
	if(char_flag == 0)
	{
			error("Empty line in the map!");
			exit(FAIL);
	}
}

//if it's part of the map - return 1
int is_map_line(const char *line)
{
    int x = 0; 
    if(line[x] == ' ' || line[x] == '1' || line[x] == '0')
        return 1;
    return (0);
}

//parse the file - store data in the structs 
int	map_read(t_game *game, char *file)
{
	int	fd;
	int	i;
	int	rows;
    rows = 0;

	i = 0;
    int x; 
    x = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (FAIL);
    char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		rows++; 
		free(line);
	}
    close(fd);
	fd = open(file, O_RDONLY);
	game->buffer = (char **)malloc(((rows) + 1) * sizeof(char *));
    game->map = (char **)malloc(((rows) + 1) * sizeof(char *));
	if (!game->buffer || !game->map)
		ft_exit_simple(game);
	while (rows > 0)
	{
        game->buffer[i] = get_next_line(fd);
        if(is_map_line(game->buffer[i]))
        {
			check_empty_line(game->buffer[i]);
            game->map[x] = ft_strdup(game->buffer[i]);
            x++;
        }
		rows--;
		i++;
	}
	game->buffer[i] = NULL;
    game->map[x] = NULL;
	return (SUCCESS);
}

