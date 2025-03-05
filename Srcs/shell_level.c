/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:32:33 by ls                #+#    #+#             */
/*   Updated: 2024/06/21 08:06:21 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	set_fd_shell_level(int *fd, int flag1, int flag2)
{
	*fd = open(".shell_level", flag1 | flag2, 0644);
	if (*fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void	init_shell_level(t_shell_level *sl, int flag1, int flag2)
{
	set_fd_shell_level(&sl->fd, flag1, flag2);
	sl->number = 0;
	ft_reset_buffer(sl->buffer, 16);
	sl->bytes_read = 0;
	ft_reset_buffer(sl->number_str, 16);
	sl->length = 0;
	sl->temp_number = 0;
	sl->temp = 0;
}

void	set_number_str(t_shell_level *sl)
{
	int	i;

	i = 0;
	sl->temp_number = sl->number;
	while (sl->temp_number > 0)
	{
		sl->number_str[sl->length++] = (sl->temp_number % 10) + '0';
		sl->temp_number /= 10;
	}
	if (sl->length == 0)
		sl->number_str[sl->length++] = '0';
	sl->number_str[sl->length] = '\0';
	while (i < sl->length / 2)
	{
		sl->temp = sl->number_str[i];
		sl->number_str[i] = sl->number_str[sl->length - 1 - i];
		sl->number_str[sl->length - 1 - i] = sl->temp;
		i++;
	}
}

void	add_number_shell_level(void)
{
	t_shell_level	sl;

	init_shell_level(&sl, O_RDWR, O_CREAT);
	sl.bytes_read = read(sl.fd, sl.buffer, sizeof(sl.buffer) - 1);
	if (sl.bytes_read > 0)
	{
		sl.buffer[sl.bytes_read] = '\0';
		sl.number = ft_atoi(sl.buffer);
		if (sl.number < 0)
			sl.number = 0;
		else
			sl.number++;
	}
	else
		sl.number = 1;
	set_number_str(&sl);
	close(sl.fd);
	sl.fd = open(".shell_level", O_WRONLY | O_TRUNC);
	if (sl.fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	write(sl.fd, sl.number_str, sl.length);
	close(sl.fd);
}

void	reduce_number_shell_level(void)
{
	t_shell_level	sl;

	init_shell_level(&sl, O_RDWR, O_CREAT);
	sl.bytes_read = read(sl.fd, sl.buffer, sizeof(sl.buffer) - 1);
	if (sl.bytes_read > 0)
	{
		sl.buffer[sl.bytes_read] = '\0';
		sl.number = ft_atoi(sl.buffer);
		if (sl.number > 0)
			sl.number = sl.number - 1;
		else
			sl.number = 0;
	}
	else
		sl.number = 0;
	set_number_str(&sl);
	close(sl.fd);
	sl.fd = open(".shell_level", O_WRONLY | O_TRUNC);
	if (sl.fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	write(sl.fd, sl.number_str, sl.length);
	close(sl.fd);
}
