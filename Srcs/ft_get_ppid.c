/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ppid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:46:57 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 07:49:47 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	get_ppid_value(char **ppid_str, int *p_pid)
{
	if (*ppid_str)
	{
		*ppid_str += 5;
		while (**ppid_str == ' ' || **ppid_str == '\t')
			(*ppid_str)++;
		*p_pid = ft_atoi(*ppid_str);
	}
}

int	ft_get_ppid(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;
	pid_t	ppid;
	char	*ppid_str;

	ppid = -1;
	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
	{
		perror("read");
		close(fd);
		exit(EXIT_FAILURE);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	ppid_str = ft_strstr(buffer, "PPid:");
	get_ppid_value(&ppid_str, &ppid);
	return (ppid);
}
