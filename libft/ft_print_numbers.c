/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:20:01 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/21 17:20:02 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	x;

	x = 0;
	if (n <= 0)
	{
		n *= -1;
		x++;
	}
	while (n > 0)
	{
		n = n / 10;
		x++;
	}
	return (x);
}

int	ft_print_numbers(int x)
{
	if (x == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	ft_putnbr_fd(x, 1);
	return (ft_intlen(x));
}
