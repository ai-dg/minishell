/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_resize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:00:01 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 15:12:37 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	resize_exit_status(int exit_status)
{
	if (exit_status > 256)
		while (exit_status > 256)
			exit_status = exit_status - 256;
	if (exit_status < 0)
		while (exit_status < 0)
			exit_status = exit_status + 256;
	return (exit_status);
}

bool	only_numbers(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (false);
		i++;
	}
	return (true);
}
