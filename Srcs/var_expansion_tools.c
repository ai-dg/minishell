/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:31:08 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/22 16:29:47 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_count_occurences(char c, char *str)
{
	int	i;
	int	acc;

	i = 0;
	acc = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
		{
			if (i > 0 && str[i - 1] == 127)
				i++;
			else if (str[i + 1] != '\0' && (str[i + 1] != ' ' && str[i
						+ 1] != '$'))
				acc++;
		}
		i++;
	}
	return (acc);
}

int	var_length(char *str, int index)
{
	int	i;

	i = index;
	if (ft_strlen(&str[i]) == 1 && str[i] == '$')
		return (1);
	else if (str[index + 1] && str[index + 1] == '$')
		return (2);
	else if (str[index + 1] && str[index + 1] == '?')
		return (2);
	else if (str[index + 1] && ft_isdigit(str[index + 1]))
		return (2);
	else if (str[index + 1] && (str[index + 1] == ' ' || str[index
				+ 1] == '\0'))
		return (1);
	index++;
	while (str[index] != '$')
	{
		if (!is_authorized_char(str[index]))
			break ;
		index++;
	}
	return (index - i);
}

int	count_bar_before_dollar(char *str, int index)
{
	int	i;
	int	acc;

	i = index;
	acc = 0;
	while (i >= 0)
	{
		if (str[i] != '\\')
			break ;
		if (str[i] == '\\')
			acc++;
		i--;
	}
	return (acc);
}

int	is_authorized_char(char c)
{
	if (!ft_isprint(c) || c == '$' || c == '\\' || c == '\'' || c == '"'
		|| c == '=' || c == ' ' || c == '\n' || c == ']' || c == '%' || c == '/'
		|| c == '*' || c == '.')
		return (false);
	return (true);
}

bool	has_to_ignore(char c)
{
	if (c == ':' || c == '=' || c == '.' || c == ',' || c == '%' || c == '"'
		|| c == '\'')
		return (true);
	return (false);
}
