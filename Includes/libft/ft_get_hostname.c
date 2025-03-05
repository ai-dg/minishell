/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hostname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:32:15 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 10:32:37 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_gethostname(char *buff, int buffer_size)
{
	int	fd;
	int	i;

	i = 0;
	ft_reset_buffer(buff, buffer_size);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (-1);
	read(fd, buff, buffer_size);
	while (buff[i])
	{
		if (buff[i] == '\n')
			buff[i] = 0;
		i++;
	}
	close(fd);
	return (0);
}
