/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 08:37:37 by calbor-p          #+#    #+#             */
/*   Updated: 2024/01/27 22:29:06 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*reset_buffer(char buf[BUFFER_SIZE])
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buf[i] = '\0';
		i++;
	}
	return ((void *)buf);
}

int	bufferlength(char *buf)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (++i < BUFFER_SIZE && buf[i] != '\0')
		count++;
	return (count);
}

void	handle_buf(char *buf, size_t start, size_t length)
{
	char	*left;
	int		i;

	i = -1;
	left = NULL;
	if ((int)start < 0)
		start = 0;
	if (length > 0 && start + length <= (size_t)bufferlength(buf))
	{
		left = ft_substr(buf, start, length);
		reset_buffer(buf);
		if (length >= 1)
			while (left[++i])
				buf[i] = left[i];
		free(left);
	}
	else
		reset_buffer(buf);
}
