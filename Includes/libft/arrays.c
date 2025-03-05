/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:25:12 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 15:19:18 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_array(char c, char *params)
{
	int	i;

	i = 0;
	if (!params)
		return (-1);
	while (params[i])
	{
		if (c == params[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_dollar_index(char c, char *params)
{
	int	i;

	i = 0;
	if (!params)
		return (-1);
	while (params[i])
	{
		if (params[i] == c)
		{
			if (i > 0 && params[i - 1] == 127)
				i++;
			else
				return (i);
		}
		i++;
	}
	return (-1);
}

int	find_index(char c, char *params)
{
	int	i;

	i = 0;
	if (!params)
		return (-1);
	while (params[i])
	{
		if (params[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	check_isolated_start_end(char c, char *params, int params_len)
{
	if (params[0] == c)
	{
		if (params_len == 1)
		{
			return (0);
		}
		else if (params[1] == ' ' || params[1] == '/')
		{
			return (0);
		}
	}
	if (params_len > 1 && params[params_len - 1] == c
		&& params[params_len - 2] == ' ')
	{
		return (params_len - 1);
	}
	return (-1);
}

int	find_isolated(char c, char *params)
{
	int	i;
	int	params_len;
	int	result;

	i = 1;
	if (!params)
		return (-1);
	params_len = (int)ft_strlen(params);
	if (params_len == 0)
		return (-1);
	result = check_isolated_start_end(c, params, params_len);
	if (result != -1)
		return (result);
	while (i < params_len - 1)
	{
		if (params[i] == c && params[i - 1] == ' ' && (params[i + 1] == ' '
				|| params[i + 1] == '/'))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
