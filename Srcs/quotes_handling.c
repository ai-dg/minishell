/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 07:16:33 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 23:20:44 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static bool	handle_quotes(char *str, int *i, int *index, char pending)
{
	while (str[*i] && str[*i] != pending)
	{
		if (*i > *index && pending == '"')
			return (false);
		if (*i > *index && pending == '\'')
			return (false);
		(*i)++;
	}
	return (true);
}

bool	swap_foreward_in_lang(char *str, int index)
{
	int		i;
	char	pending;
	bool	result;

	i = 0;
	pending = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\'' && str[i] != '"')
			i++;
		if (i > index || i == (int)ft_strlen(str))
			return (true);
		pending = str[i++];
		result = true;
		result = handle_quotes(str, &i, &index, pending);
		if (result == false)
			return (false);
		pending = 0;
		if (i > index && pending == 0)
			return (false);
		i++;
	}
	if (i > index && pending == 0)
		return (false);
	return (true);
}

bool	swap_foreward(char *str, int index)
{
	int		i;
	char	pending;

	i = 0;
	pending = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\'' && str[i] != '"')
			i++;
		if (i > index || i == (int)ft_strlen(str))
			return (true);
		pending = str[i++];
		while (str[i] && str[i] != pending)
		{
			if (i > index && pending == '"')
				return (true);
			if (i > index && pending == '\'')
				return (false);
			i++;
		}
		pending = 0;
		i++;
	}
	return (true);
}

static bool	return_swap_back(bool *dble_closed, bool *sple_closed, char *prior)
{
	if (*dble_closed && *sple_closed)
		*prior = 0;
	if (*prior == '"' && *dble_closed)
		return (true);
	if (*prior == '"' && *sple_closed == false)
		return (true);
	if (*sple_closed == false && *dble_closed)
		return (false);
	if (*prior == '\'' && !*sple_closed)
		return (false);
	return (*sple_closed);
}

bool	swap_back(char *str, int index)
{
	bool	sple_closed;
	bool	dble_closed;
	char	prior;
	bool	result;

	prior = 0;
	sple_closed = true;
	dble_closed = true;
	while (index >= 0)
	{
		if (str[index] == '\'')
			sple_closed = ft_toogle(sple_closed);
		if (str[index] == '"')
			dble_closed = ft_toogle(dble_closed);
		if (str[index] == '"' || str[index] == '\'')
			prior = str[index];
		index--;
	}
	result = return_swap_back(&dble_closed, &sple_closed, &prior);
	return (result);
}
