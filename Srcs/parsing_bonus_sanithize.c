/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_sanithize.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/26 07:53:10 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_unallocated_trim(char *str)
{
	int	start;
	int	end;

	start = 0;
	if (!str)
		return ;
	end = ft_strlen(str);
	if (ft_is_whitespace(str[start]))
	{
		while (str[start] && ft_is_whitespace(str[start]))
			start++;
		ft_memmove(str, &str[start], ft_strlen(&str[start]));
		str[end - start] = 0;
	}
	end = ft_strlen(str) - 1;
	if (end >= 1 && ft_is_whitespace(str[end]))
	{
		while (end >= 1 && str[end - 1] && ft_is_whitespace(str[end - 1]))
			end--;
		str[end] = 0;
	}
}

void	ft_unallocated_trim_once(char *str, char c)
{
	int	start;
	int	end;

	start = 0;
	if (!str)
		return ;
	end = ft_strlen(str);
	if (str[start] == c)
	{
		ft_memmove(str, &str[1], ft_strlen(&str[1]));
		str[end - 1] = 0;
	}
	end = ft_strlen(str) - 1;
	if (end >= 1 && str[end] == c)
	{
		str[end] = 0;
	}
}

void	ft_symetric_trim_parenthesis(char *str)
{
	char	buffer[1024];

	if (!str)
		return ;
	reset_buf(buffer, 1024);
	while (can_trim_parenthesis(str))
	{
		ft_strlcpy(buffer, &str[1], ft_strlen(str));
		reset_buf(str, (int)ft_strlen(str));
		ft_strlcpy(str, buffer, ft_strlen(buffer));
	}
}

void	sanithize_prompt(char *prompt)
{
	while (has_white_space(prompt) || can_trim_parenthesis(prompt))
	{
		ft_symetric_trim_parenthesis(prompt);
		ft_unallocated_trim(prompt);
	}
}

void	sanithize_prompts(char **prompts)
{
	int	i;

	i = 0;
	while (prompts[i])
	{
		sanithize_prompt(prompts[i]);
		i++;
	}
}
