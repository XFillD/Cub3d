/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:25:27 by yalechin          #+#    #+#             */
/*   Updated: 2024/01/21 16:25:28 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_return_format(char f, int count, va_list args)
{
	if (f == 'c')
		count += ft_print_char(va_arg(args, int));
	if (f == 'd' || f == 'i')
		count += ft_print_numbers(va_arg(args, int));
	if (f == 's')
		count += ft_print_strings(va_arg(args, char *));
	if (f == 'x')
		count += ft_print_hex_l(va_arg(args, unsigned int));
	if (f == 'X')
		count += ft_print_hex_u(va_arg(args, unsigned int));
	if (f == '%')
	{
		ft_putchar_fd('%', 1);
		count++;
	}
	if (f == 'u')
		count += ft_print_unsigned(va_arg(args, unsigned int));
	if (f == 'p')
		count += ft_print_pointer(va_arg(args, unsigned long long int));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count = ft_return_format(*format, count, args);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}
