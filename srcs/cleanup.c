/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhauba <fhauba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:55:19 by fhauba            #+#    #+#             */
/*   Updated: 2024/11/14 15:35:01 by fhauba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_textures(t_game *game)
{
	if (game->north_texture)
	{
		mlx_delete_texture(game->north_texture);
		game->north_texture = NULL;
	}
	if (game->south_texture)
	{
		mlx_delete_texture(game->south_texture);
		game->south_texture = NULL;
	}
	if (game->west_texture)
	{
		mlx_delete_texture(game->west_texture);
		game->west_texture = NULL;
	}
	if (game->east_texture)
	{
		mlx_delete_texture(game->east_texture);
		game->east_texture = NULL;
	}
}

void	free_floor_ceiling(t_design_config *config)
{
	if (config)
	{
		if (config->floor_color[0])
			free(config->floor_color);
		if (config->ceiling_color[0])
			free(config->ceiling_color);
	}
}

void	free_design_config(t_design_config *config)
{
	if (config)
	{
		if (config->north_texture)
		{
			free(config->north_texture);
			config->north_texture = NULL;
		}
		if (config->south_texture)
		{
			free(config->south_texture);
			config->south_texture = NULL;
		}
		if (config->west_texture)
		{
			free(config->west_texture);
			config->west_texture = NULL;
		}
		if (config->east_texture)
		{
			free(config->east_texture);
			config->east_texture = NULL;
		}
		free(config);
	}
}
