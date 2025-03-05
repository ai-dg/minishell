/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 18:00:06 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ');
}

bool	if_quote(char c)
{
	if (c == 39 || c == 34)
		return (true);
	return (false);
}

bool	if_trim(char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (true);
	return (false);
}

static void	fill_total_args(char *str, int *i, int *count, int *in_args)
{
	int	quote;

	quote = 0;
	while (str[*i] && str[*i] != '\n')
	{
		if (if_quote(str[*i]) == true)
			quote++;
		if (if_trim(str, *i) == true && quote % 2 == 0)
		{
			(*count)++;
			*in_args = 0;
		}
		else if (str[*i] <= 32 && quote % 2 == 0)
		{
			if (*in_args)
				*in_args = 0;
		}
		else if (!*in_args)
		{
			*in_args = 1;
			(*count)++;
		}
		(*i)++;
	}
}

int	count_total_args(char *str)
{
	int	i;
	int	count;
	int	in_args;

	i = 0;
	count = 0;
	in_args = 0;
	fill_total_args(str, &i, &count, &in_args);
	return (count);
}
