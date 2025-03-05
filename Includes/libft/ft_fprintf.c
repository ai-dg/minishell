/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/25 12:20:21 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_string(char *string, int *length)
{
	if (!string && !*string)
		string = "(null)";
	while (*string)
		*length += write(1, string++, 1);
}

static void	put_digit(long long int number, int base, int *length)
{
	char	*hexadecimal;

	hexadecimal = "0123456789abcdef";
	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number >= base)
		put_digit((number / base), base, length);
	*length += write(1, &hexadecimal[number % base], 1);
}

static void	print_all_values(const char *format, va_list args, int *length)
{
	while (*format)
	{
		if ((*format == '%') && ((*(format + 1) == 's') || (*(format
						+ 1) == 'd') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				put_string(va_arg(args, char *), length);
			else if (*format == 'd')
				put_digit((long long int)va_arg(args, int), 10, length);
			else if (*format == 'x')
				put_digit((long long int)va_arg(args, unsigned int), 16,
					length);
		}
		else
			length += write(1, format, 1);
		format++;
	}
}

int	ft_fprintf(FILE *stream, const char *format, ...)
{
	int		length;
	va_list	args;
	int		stdout_backup;

	if (!format && !*format)
		return (-1);
	length = 0;
	ft_fflush(stdout);
	stdout_backup = dup(ft_fileno(stdout));
	dup2(ft_fileno(stream), ft_fileno(stdout));
	va_start(args, format);
	print_all_values(format, args, &length);
	va_end(args);
	ft_fflush(stdout);
	dup2(stdout_backup, ft_fileno(stdout));
	close(stdout_backup);
	return (length);
}
