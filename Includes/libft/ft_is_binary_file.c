/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_binary_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:33 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:48:03 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	has_binary_data(char *buff, int reads)
{
	int	i;

	i = 0;
	while (i < reads)
	{
		if ((buff[i] < 9 || buff[i] > 13) && (buff[i] < 32 || buff[i] > 126)
			&& buff[i] != '\0')
			return (true);
		i++;
	}
	return (false);
}

bool	ft_is_binary_file(char *path)
{
	int		reads;
	int		fd;
	char	buff[1024];

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	reads = read(fd, buff, sizeof(buff));
	while ((reads) > 0)
	{
		if (has_binary_data(buff, reads))
		{
			close(fd);
			return (true);
		}
		ft_reset_buffer(buff, reads);
	}
	close(fd);
	return (false);
}
