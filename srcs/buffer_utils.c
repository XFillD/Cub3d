/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:23:30 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/16 16:51:59 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	init_arrays(t_game *game, int rows)
{
	game->buffer = (char **)malloc(((rows) + 1) * sizeof(char *));
	game->map = (char **)malloc(((rows) + 1) * sizeof(char *));
	if (!game->buffer || !game->map)
		ft_exit_simple(game);
}

void	get_colours(char *buffer, int *r, int *g, int *b)
{
	while (*buffer == ' ')
		buffer++;
	*r = ft_atoi(buffer);
	while (*buffer && ft_isdigit(*buffer))
		buffer++;
	if (*buffer == ',')
	{
		buffer++;
	}
	*g = ft_atoi(buffer);
	while (*buffer && ft_isdigit(*buffer))
		buffer++;
	if (*buffer == ',')
	{
		buffer++;
	}
	*b = ft_atoi(buffer);
}

int	buffer_check_content(char **buffer, int rows, char *find)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		if (ft_strncmp2(buffer[i], find, ft_strlen(find)) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	buffer_check(char **buffer, int rows)
{
	if (buffer_check_content(buffer, rows, "NO "))
		return (FAIL);
	if (buffer_check_content(buffer, rows, "SO "))
		return (FAIL);
	if (buffer_check_content(buffer, rows, "EA "))
		return (FAIL);
	if (buffer_check_content(buffer, rows, "WE "))
		return (FAIL);
	if (buffer_check_content(buffer, rows, "C "))
		return (FAIL);
	if (buffer_check_content(buffer, rows, "F "))
		return (FAIL);
	return (SUCCESS);
}
