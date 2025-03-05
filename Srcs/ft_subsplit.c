/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 08:24:04 by ls                #+#    #+#             */
/*   Updated: 2024/07/01 15:54:02 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	count_words_in_sub_array(char **array)
{
	int	i;
	int	length;

	length = 0;
	i = 0;
	while (array[i])
	{
		length += count_word(array[i], ' ');
		i++;
	}
	return (length);
}

char	**fill_array(char **words, char *to_split)
{
	int		j;
	char	**splitted;

	j = 0;
	splitted = ft_split_quotes_alt(to_split, NULL);
	if (!splitted)
		return (free_array(&words), NULL);
	while (splitted[j])
	{
		words = ft_push_chars_to_array(words, splitted[j]);
		j++;
	}
	free_array(&splitted);
	return (words);
}

static bool	if_echo_in_args(char ***words, int *i)
{
	int	x;

	x = *i;
	while (x >= 0)
	{
		if (ft_strstr((*words)[x], "echo") != NULL)
			return (true);
		x--;
	}
	return (false);
}

char	**ft_subsplit(char **array)
{
	int		i;
	char	**words;

	words = NULL;
	i = 0;
	while (array[i])
	{
		if (find_index(' ', array[i]) > -1)
		{
			if (i > 0 && if_echo_in_args(&words, &i) == true
				&& find_index('|', array[i]) > -1)
				words = ft_push_chars_to_array(words, array[i]);
			else
				words = fill_array(words, array[i]);
		}
		else
		{
			words = ft_push_chars_to_array(words, array[i]);
		}
		if (!words)
			return (free_array(&array), free_array(&words), NULL);
		i++;
	}
	return (free_array(&array), words);
}
