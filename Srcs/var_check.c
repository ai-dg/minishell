/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:25:02 by ls                #+#    #+#             */
/*   Updated: 2024/06/30 16:31:08 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	has_forbidden_sign(char *key)
{
	int	i;
	int	index;

	index = find_index('=', key);
	index--;
	i = 0;
	while (key[i] && i < index)
	{
		if (key[i] == '+')
			return (true);
		i++;
	}
	return (false);
}

bool	is_a_sum(char *key)
{
	int	index;

	index = find_index('=', key);
	if (index == -1)
		index = ft_strlen(key);
	index--;
	if (index < 0)
		return (false);
	if (key[index] == '+')
		return (true);
	return (false);
}

bool	has_forbidden_char(char *key)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_' && key[i] != '+')
			return (true);
		i++;
	}
	if (has_forbidden_sign(key))
		return (true);
	return (false);
}

/**
 * @brief is_valid_variable test if the char is a variable that complies
 * exigence
 * 			bool is_valid_variable(char *key)
 * @param char* is the variable name to test
 *
 * @return bool return true if the name of the variable is ok
 */
bool	is_valid_variable(char *key)
{
	if (!key || ft_strlen(key) == 0)
		return (false);
	if (key[0] == '=')
		return (false);
	if (ft_isdigit(key[0]))
		return (false);
	if (has_forbidden_char(key))
		return (false);
	return (true);
}
