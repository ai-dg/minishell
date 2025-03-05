/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_sanithize_tools.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/18 12:38:27 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	can_trim_parenthesis(char *prompt)
{
	int	i;
	int	balance;
	int	len;
	int	highest;

	highest = 0;
	balance = 0;
	i = 0;
	len = ft_strlen(prompt) - 1;
	while (prompt[i])
	{
		if (prompt[i] == '(')
		{
			balance++;
			highest = balance;
		}
		if (prompt[i] == ')')
			balance--;
		if (balance == 0 && i != len)
			return (false);
		i++;
	}
	if (balance == 0 && highest > 0)
		return (true);
	return (false);
}

bool	has_white_space(char *prompt)
{
	int	len;

	len = ft_strlen(prompt) - 1;
	return (ft_is_whitespace(prompt[0]) || ft_is_whitespace(prompt[len]));
}

bool	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
