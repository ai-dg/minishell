/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:26:49 by calbor-p          #+#    #+#             */
/*   Updated: 2023/12/22 18:01:37 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_argslength(const char *str, char tests[9])
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (str[i])
	{
		if (!is_in_array(str[i], tests))
			count++;
		if (is_in_array(str[i], tests))
		{
			count++;
			break ;
		}
		i++;
	}
	if (count == (int)ft_strlen(str) && !is_in_array(str[ft_strlen(str) - 1],
			tests))
		return (0);
	return (count);
}

static int	get_index(char c, char tests[9])
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (tests[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	handle_arg(char *str, va_list args, char test[9], size_t *pos)
{
	int			index;
	int			reads;
	int			p_len;
	char		*params;
	static int	(*handle_f[9])(va_list args, char *params) = {handle_char,
		handle_string, handle_pointer, handle_int, handle_int, handle_unsigned,
		handle_hexlower, handle_hexupper, handle_percent};

	p_len = get_argslength(str, test);
	reads = 0;
	*pos = *pos + (size_t)p_len;
	if (p_len == 0)
		return (-1);
	params = ft_substr(str, 1, (size_t)p_len);
	index = get_index(params[ft_strlen(params) - 1], test);
	if (index != -1)
		reads += handle_f[index](args, params);
	free(params);
	return (reads);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	size_t		i;
	int			reads;
	static char	test[9] = {'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'};

	reads = 0;
	if (!str || str == NULL)
		return (-1);
	i = 0;
	va_start(args, str);
	while (str[i] && i < ft_strlen(str))
	{
		if (str[i] != '%')
			reads += write_char(str[i]);
		if (str[i] == '%')
			reads += handle_arg((char *)&str[i], args, test, &i);
		i++;
	}
	va_end(args);
	return (reads);
}
/*
int	main(void)
{
	int a;
	int b;

	//char * null_str = NULL;

	// int *c = &a;

	ft_printf("\nft_printf------------\n");
	b = ft_printf("%012x", LONG_MIN);
	printf("\nprintf------------\n");
	a = printf("%012x", LONG_MIN);
	printf("\n");
	printf("------------\n");
	printf("res ft%d\n",b);
	printf("res nr%d\n",a);


	return (1);
}*/
// test 216