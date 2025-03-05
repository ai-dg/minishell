/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:36:27 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 10:36:49 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reset_buffer(char *buff, int buffer_size)
{
	int	i;

	i = 0;
	if (!buff)
		return ;
	while (i < buffer_size)
	{
		buff[i] = 0;
		i++;
	}
}
