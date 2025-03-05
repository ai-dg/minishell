/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 07:05:50 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/12 16:20:14 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*reset_buf(char *buf, int length)
{
	int	i;

	i = 0;
	if (buf == NULL)
		return (NULL);
	while (i < length)
	{
		buf[i] = 0;
		i++;
	}
	return (buf);
}
