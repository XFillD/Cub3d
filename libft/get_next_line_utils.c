/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:51:19 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/13 15:42:13 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_g(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			x;
	size_t			s;

	s = nmemb * size;
	if ((nmemb && size) && nmemb > ((size_t)-1) / size)
		return (NULL);
	x = 0;
	ptr = (unsigned char *)malloc(s);
	if (!ptr)
		return (NULL);
	while (x < (s))
	{
		ptr[x++] = 0;
	}
	return (ptr);
}

char	*ft_strchr_g(const char *s, int c)
{
	int	x;

	x = 0;
	while (s[x])
	{
		if (s[x] == (char)c)
		{
			return ((char *)s + x);
		}
		x++;
	}
	if (c == '\0')
		return ((char *)s + x);
	return (NULL);
}

size_t	ft_strlen_g(const char *s)
{
	int	x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

char	*ft_strjoin_g(char const *s1, char const *s2)
{
	size_t	x;
	size_t	y;
	char	*ptr;

	x = 0;
	y = 0;
	ptr = (char *)malloc(ft_strlen_g(s1) + ft_strlen_g(s2) + 1);
	if (!ptr)
		return (NULL);
	while (x < ft_strlen_g(s1))
	{
		ptr[x] = s1[x];
		x++;
	}
	while (y < ft_strlen_g(s2))
	{
		ptr[x] = s2[y];
		x++;
		y++;
	}
	ptr[x] = '\0';
	return (ptr);
}

char	*ft_strdup_g(const char *s)
{
	char	*ptr;
	int		x;
	int		len;

	len = ft_strlen_g(s);
	ptr = (char *)malloc((len + 1));
	if (!ptr)
		return (NULL);
	x = 0;
	while (s[x])
	{
		ptr[x] = s[x];
		x++;
	}
	ptr[x] = '\0';
	return (ptr);
}
