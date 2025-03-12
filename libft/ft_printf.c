/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:50:19 by rmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/31 18:16:06 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conver(va_list args, const char format)
{
	int		len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		len += ft_put_hex_ptr((size_t)va_arg(args, void *), 'x', 1);
	else if (format == 'd' || format == 'i')
		len += ft_putnbr_fd(va_arg(args, int), 1);
	else if (format == 'u')
		len += ft_putnbr_fd(va_arg(args, unsigned int), 1);
	else if (format == 'x')
		len += ft_put_hex_ptr(va_arg(args, unsigned int), 'x', 0);
	else if (format == 'X')
		len += ft_put_hex_ptr(va_arg(args, unsigned int), 'X', 0);
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(char const *s, ...)
{
	int		i;
	va_list	args;
	int		len;

	i = 0;
	len = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			len += ft_conver(args, s[i + 1]);
			i++;
		}
		else
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (len);
}

/*#include <stdio.h>

int	main(void)
{
	int original_print_return;
	int fake_print_return;
	
	close(STDOUT_FILENO);

	fake_print_return = ft_printf("Esto es un caracter: %c\n", 'W');
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un caracter: %c\n", 'W');
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un string: %s\n", "Hola que tal?");
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un string: %s\n", "Hola que tal?");
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un string NULL: %s\n", (char *)NULL);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un string NULL: %s\n", (char *)NULL);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un entero negativo: %d\n", -42);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un entero negativo: %d\n", -42);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un unsigned int: %u\n", 42);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un unsigned int: %u\n", 42);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex en minusculas: %x\n", 255);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex en minusculas: %x\n", 255);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex 0 en minusculas: %x\n", 0);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex 0 en minusculas: %x\n", 0);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex en mayusculas: %X\n", 255);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex en mayusculas: %X\n", 255);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un hex 0 en mayusculas: %X\n", 0);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un hex 0 en mayusculas: %X\n", 0);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	int	n = 42;
	fake_print_return = ft_printf("Esto es un puntero: %p\n", &n);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un puntero: %p\n", &n);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un porcentaje: %%\n");
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un porcentaje: %%\n");
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('\n', 2);

	if (original_print_return != fake_print_return)
		ft_putstr_fd("ALERTA, ALERTA!\n\n", STDERR_FILENO);

	fake_print_return = ft_printf("Esto es un vacío: %p\n", NULL);
	ft_putnbr_fd(fake_print_return, 2);
	ft_putchar_fd('\n', 2);
	original_print_return = printf("Esto es un vacío: %p\n", NULL);
	ft_putnbr_fd(original_print_return, 2);
	ft_putchar_fd('\n', 2);
	
	return (0);
}*/