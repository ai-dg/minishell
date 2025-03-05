/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling_mask.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:18:09 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/19 11:21:57 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	has_dollar_indicator(char *str)
{
	char	indicator_dollar;
	int		i;

	indicator_dollar = 0x1D;
	i = 0;
	while (str[i])
	{
		if (str[i] == indicator_dollar)
			return (true);
		i++;
	}
	return (false);
}

bool	has_quotes(char *str)
{
	int		i;
	char	indicator_double;
	char	indicator_single;

	indicator_double = 0x1F;
	indicator_single = 0x1E;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == indicator_double
			|| str[i] == indicator_single)
			return (true);
		i++;
	}
	return (false);
}
