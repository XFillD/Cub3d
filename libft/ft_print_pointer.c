/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:07:33 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/27 19:07:34 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_pointer(unsigned long long n)
{
	int	x;

	x = 0;
	while (n > 0)
	{
		n = n / 16;
		x++;
	}
	return (x);
}

static void	ft_put_pointer(unsigned long long x)
{
	if (x < 10)
	{
		ft_putchar_fd((x + '0'), 1);
	}
	if (x > 10 && x < 16)
	{
		ft_putchar_fd((x + 87), 1);
	}
	if (x >= 16)
	{
		ft_put_pointer(x / 16);
		ft_put_pointer(x % 16);
	}
}

int	ft_print_pointer(unsigned long long x)
{
	if (x == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	write(1, "0x", 2);
	ft_put_pointer(x);
	return (ft_count_pointer(x) + 2);
}
