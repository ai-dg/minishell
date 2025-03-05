/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 07:05:33 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_root_split_index(char *prompt)
{
	int	i;
	int	index;
	int	parenthesis;

	parenthesis = 0;
	index = 0;
	i = 0;
	ft_unallocated_trim(prompt);
	ft_symetric_trim_parenthesis(prompt);
	while (prompt[i])
	{
		if (prompt[i] == '(')
			parenthesis++;
		if (prompt[i] == ')')
			parenthesis--;
		if ((ft_strncmp(&prompt[i], "&&", 2) == 0 || ft_strncmp(&prompt[i],
					"||", 2) == 0) && parenthesis + 1 == 1)
		{
			index = i;
			return (index);
		}
		i++;
	}
	return (index);
}

int	get_root_split_index_rev(char *prompt)
{
	int	i;
	int	index;
	int	parenthesis;

	parenthesis = 0;
	ft_unallocated_trim(prompt);
	index = 0;
	i = (int)ft_strlen(prompt) - 1;
	while (i >= 0 && prompt[i])
	{
		if (prompt[i] == '(')
			parenthesis--;
		if (prompt[i] == ')')
			parenthesis++;
		if ((has_ops(&prompt[i]) && parenthesis + 1 == 1)
			|| (has_ops(&prompt[i]) && parenthesis == 0))
		{
			index = i;
			return (index);
		}
		i--;
	}
	return (index);
}

static void	fill_splited_with_index(int *index, char **temp, char ***splitted)
{
	int	i;

	i = 0;
	while (*index)
	{
		(*splitted)[i] = ft_substr(*temp, 0, *index);
		*temp += *index;
		i++;
		(*splitted)[i] = ft_substr(*temp, 0, 2);
		*temp += 2;
		*index = get_root_split_index(*temp);
		i++;
		if (*index == 0 && *temp)
		{
			(*splitted)[i] = ft_substr(*temp, 0, ft_strlen(*temp));
			i++;
		}
	}
	(*splitted)[i] = NULL;
}

char	**ft_split_at_law_index(char *prompt)
{
	char	**splitted;
	char	*temp;
	int		index;

	temp = prompt;
	splitted = malloc(20 * sizeof(char *));
	if (!splitted)
		return (NULL);
	index = get_root_split_index(temp);
	fill_splited_with_index(&index, &temp, &splitted);
	return (splitted);
}

char	**ft_split_at_index(char *prompt, int index)
{
	char	**splitted;

	splitted = malloc(4 * sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted[0] = ft_substr(prompt, 0, index);
	splitted[1] = ft_substr(prompt, index + 2, ft_strlen(prompt) - index - 2);
	splitted[2] = ft_substr(prompt, index, 2);
	splitted[3] = NULL;
	return (splitted);
}
