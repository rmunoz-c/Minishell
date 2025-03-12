/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:22:35 by rmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/31 17:11:32 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	return (ft_strlen(s));
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_put_hex_ptr(size_t n, const char format, int is_ptr)
{
	int	printed_chars;

	printed_chars = 0;
	if (is_ptr && n == 0)
		return (ft_putstr("(nil)"));
	else if (is_ptr)
		printed_chars += ft_putstr("0x");
	if (n == 0)
		return (printed_chars + ft_putchar('0'));
	if (n >= 16)
		printed_chars += ft_put_hex_ptr(n / 16, format, 0);
	if (n % 16 <= 9)
		printed_chars += ft_putchar((n % 16 + '0'));
	else if (format == 'x' || is_ptr)
		printed_chars += ft_putchar((n % 16 - 10 + 'a'));
	else if (format == 'X')
		printed_chars += ft_putchar((n % 16 - 10 + 'A'));
	return (printed_chars);
}
