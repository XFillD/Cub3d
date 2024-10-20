/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_l.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:06:57 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/27 19:06:58 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(unsigned int n)
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

static void	ft_put_hex(unsigned int x)
{
	if (x < 10)
	{
		ft_putchar_fd((x + '0'), 1);
	}
	if (x >= 10 && x < 16)
		ft_putchar_fd((x + 87), 1);
	if (x >= 16)
	{
		ft_put_hex(x / 16);
		ft_put_hex(x % 16);
	}
}

int	ft_print_hex_l(unsigned int x)
{
	if (x == 0)
	{
		ft_putstr_fd("0", 1);
		return (1);
	}
	else
		ft_put_hex(x);
	return (ft_intlen(x));
}
