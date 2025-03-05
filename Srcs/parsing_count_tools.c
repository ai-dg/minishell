/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 18:12:16 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	total_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '\n')
	{
		if (if_quote(str[i]) == true)
		{
			count++;
		}
		i++;
	}
	return (count);
}

int	total_quotes_double(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == 34)
		{
			count++;
		}
		i++;
	}
	return (count);
}

int	total_quotes_simple(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == 39)
		{
			count++;
		}
		i++;
	}
	return (count);
}
