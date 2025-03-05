/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:17:17 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/18 11:10:52 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strsstr(char *str, char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (ft_strstr(str, strs[i]))
			return (true);
		i++;
	}
	return (false);
}
