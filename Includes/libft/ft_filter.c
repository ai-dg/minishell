/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 07:21:26 by ls                #+#    #+#             */
/*   Updated: 2024/05/14 12:33:26 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_filter(char *tofilter, char toskip)
{
	char	*copy;
	int		i;
	int		k;

	i = 0;
	k = 0;
	copy = ft_strdup(tofilter);
	ft_bzero(tofilter, ft_strlen(tofilter));
	while (copy[i])
	{
		if (copy[i] != toskip)
		{
			tofilter[k] = copy[i];
			k++;
		}
		i++;
	}
	free(copy);
	return (tofilter);
}
