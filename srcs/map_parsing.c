/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:03:47 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/16 17:01:35 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// parse design config to the struct
void	parse_design_config(t_design_config *config, char **buffer, int rows)
{
	int	i;

	i = 0;
	if (!config)
		return ;
	while (i < rows)
	{
		if (ft_strncmp2(buffer[i], "NO ", 3) == 0)
			config->north_texture = strdup(buffer[i] + 3);
		else if (ft_strncmp2(buffer[i], "SO ", 3) == 0)
			config->south_texture = strdup(buffer[i] + 3);
		else if (ft_strncmp2(buffer[i], "WE ", 3) == 0)
			config->west_texture = strdup(buffer[i] + 3);
		else if (ft_strncmp2(buffer[i], "EA ", 3) == 0)
			config->east_texture = strdup(buffer[i] + 3);
		else if (ft_strncmp2(buffer[i], "F ", 2) == 0)
			get_colours(buffer[i] + 1, &config->floor_color[0],
				&config->floor_color[1], &config->floor_color[2]);
		else if (ft_strncmp2(buffer[i], "C ", 2) == 0)
			get_colours(buffer[i] + 1, &config->ceiling_color[0],
				&config->ceiling_color[1], &config->ceiling_color[2]);
		i++;
	}
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
	if (rows == 0)
		ft_exit_simple(game);
	return (rows);
}

void	prepare_textures(t_game *game, int i)
{
	t_design_config	*config;

	if (buffer_check(game->buffer, i))
	{
		error("MISSING VALUES IN THE MAP FILE!");
		ft_exit_simple(game);
	}
	config = (t_design_config *)ft_calloc(sizeof(t_design_config), 1);
	parse_design_config(config, game->buffer, i);
	game->design_config = config;
	remove_newline_all(game);
	game->north_texture = mlx_load_png(game->design_config->north_texture);
	game->south_texture = mlx_load_png(game->design_config->south_texture);
	game->west_texture = mlx_load_png(game->design_config->west_texture);
	game->east_texture = mlx_load_png(game->design_config->east_texture);
}

// parse the file - store data in the structs
int	map_read(t_game *game, char *file, int x, int i)
{
	int	fd;
	int	rows;

	rows = count_rows(game, file);
	fd = open(file, O_RDONLY);
	init_arrays(game, rows);
	while (rows > 0)
	{
		game->buffer[i] = get_next_line(fd);
		if (is_map_line(game, game->buffer[i], 0, 0))
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
	if (game->line_flag)
		ft_exit_simple(game);
	prepare_textures(game, i);
	return (SUCCESS);
}
