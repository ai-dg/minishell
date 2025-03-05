/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:16:00 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/25 12:20:08 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_chars(char **from, char **to)
{
	int	i;

	i = 0;
	while (from[i])
	{
		to[i] = ft_strdup(from[i]);
		i++;
	}
	to[i] = NULL;
	return (to);
}
