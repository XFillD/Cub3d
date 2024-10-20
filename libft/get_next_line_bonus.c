/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:51:31 by yalechin          #+#    #+#             */
/*   Updated: 2024/02/18 16:01:10 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_rewrite(char *buffer, char *temp)
{
	char	*hold;

	hold = ft_strjoin(buffer, temp);
	free(buffer);
	return (hold);
}

char	*ft_clean_line(char *buffer)
{
	int		x;
	char	*line;

	x = 0;
	if (!buffer)
		return (NULL);
	while (buffer[x] && buffer[x] != '\n')
		x++;
	if (buffer[x] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	x++;
	line = ft_strdup(&buffer[x]);
	free(buffer);
	return (line);
}

char	*ft_read_line(char *buffer)
{
	char	*line;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[x] && buffer[x] != '\n')
		x++;
	line = malloc(x + 2);
	if (!line)
		return (NULL);
	while (x > y)
	{
		line[y] = buffer[y];
		y++;
	}
	if (buffer[y] && buffer[y] == '\n')
		line[y++] = '\n';
	line[y] = '\0';
	return (line);
}

char	*read_from_file(char *str, int fd)
{
	int		nb;
	char	*temp;

	if (!str)
		str = ft_calloc(1, sizeof(char));
	nb = 1;
	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp || !str)
		return (NULL);
	while (nb > 0)
	{
		nb = read(fd, temp, BUFFER_SIZE);
		if (nb < 0)
		{
			free(temp);
			free(str);
			return (NULL);
		}
		temp[nb] = '\0';
		str = ft_rewrite(str, temp);
		if (ft_strchr(temp, '\n') || !str)
			break ;
	}
	free(temp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd] || !ft_strchr(buffer[fd], '\n'))
		buffer[fd] = read_from_file(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = ft_read_line(buffer[fd]);
	buffer[fd] = ft_clean_line(buffer[fd]);
	return (line);
}
