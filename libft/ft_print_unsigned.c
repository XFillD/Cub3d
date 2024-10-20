/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:07:48 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/27 19:07:49 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	if (n < 10)
		ft_putchar_fd(('0' + n), fd);
	if (n > 9)
	{
		ft_putnbr_unsigned_fd((n / 10), fd);
		ft_putnbr_unsigned_fd((n % 10), fd);
	}
}

static int	ft_intlen(unsigned int n)
{
	int	x;

	x = 0;
	if (n == 0)
	{
		x = 1;
		return (x);
	}
	while (n > 0)
	{
		n = n / 10;
		x++;
	}
	return (x);
}

int	ft_print_unsigned(unsigned int x)
{
	ft_putnbr_unsigned_fd(x, 1);
	return (ft_intlen(x));
}
