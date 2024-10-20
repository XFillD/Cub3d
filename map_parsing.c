/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:03:47 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/20 15:22:08 by fhauba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//if it's part of the map - return 1
int is_map_line(const char *line)
{
    int x = 0; 
    if(line[x] == ' ' || line[x] == '1' || line[x] == '0')
        return 1;
    return (0);
}

//parse design config to the struct
void parse_design_config(t_designConfig *config, char **buffer, int rows) {
    for (int i = 0; i < rows; i++) {
        if (strncmp(buffer[i], "NO ", 3) == 0) {
            config->north_texture = strdup(buffer[i] + 3);
        } else if (strncmp(buffer[i], "SO ", 3) == 0) {
            config->south_texture = strdup(buffer[i] + 3);
        } else if (strncmp(buffer[i], "WE ", 3) == 0) {
            config->west_texture = strdup(buffer[i] + 3);
        } else if (strncmp(buffer[i], "EA ", 3) == 0) {
            config->east_texture = strdup(buffer[i] + 3);
        } else if (strncmp(buffer[i], "F ", 2) == 0) {
            sscanf(buffer[i] + 2, "%d,%d,%d", &config->floor_color[0], &config->floor_color[1], &config->floor_color[2]);
        } else if (strncmp(buffer[i], "C ", 2) == 0) {
            sscanf(buffer[i] + 2, "%d,%d,%d", &config->ceiling_color[0], &config->ceiling_color[1], &config->ceiling_color[2]);
        }
    }
}

//parse the file - store data in the structs 
int	map_read(t_game *game, t_mlx *mlx, char *file)
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
		return (0);
    char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		rows++; 
		free(line);
	}
    close(fd);
	fd = open(file, O_RDONLY);
    printf("ROWS %d\n", rows);
	game->buffer = (char **)malloc(((rows) + 1) * sizeof(char *));
    game->map = (char **)malloc(((15) + 1) * sizeof(char *));
	if (!game->buffer || !game->map)
		exit(0); // correct this later - special exit function? 
	while (rows > 0)
	{
        game->buffer[i] = get_next_line(fd);
        if(is_map_line(game->buffer[i]))
        {
            game->map[x] = ft_strdup(game->buffer[i]);
            x++;
        }
		rows--;
		i++;
	}
    game->map[x] = NULL;

    t_designConfig *config = (t_designConfig *)malloc(sizeof(t_designConfig));
    parse_design_config(config, game->buffer, i);

    mlx->designConfig = config;

    //TEST: print the config
    printf("North Texture: %s\n", config->north_texture);
    printf("South Texture: %s\n", config->south_texture);
    printf("West Texture: %s\n", config->west_texture);
    printf("East Texture: %s\n", config->east_texture);
    printf("Floor Color: %d, %d, %d\n", config->floor_color[0], config->floor_color[1], config->floor_color[2]);
    printf("Ceiling Color: %d, %d, %d\n", config->ceiling_color[0], config->ceiling_color[1], config->ceiling_color[2]);

	return (0);
}

