/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_key_val.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:43:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/12 17:29:09 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**return_null_splitted(char **splitted, const char *s)
{
	splitted[0] = ft_strdup(s);
	splitted[1] = NULL;
	splitted[2] = NULL;
	return (splitted);
}

static size_t	get_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split_key_val(char const *s, char c)
{
	char	**splitted;
	size_t	index;
	int		i;

	i = 0;
	index = 0;
	splitted = (char **)malloc(3 * sizeof(char *));
	if (!splitted || !s)
		return (0);
	if (find_index('=', (char *)s) == -1)
		return (return_null_splitted(splitted, s));
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			splitted[index++] = ft_substr(&s[i], 0, get_len(&s[i], c));
			i += get_len(&s[i], c) + 1;
			splitted[index++] = ft_substr(&s[i], 0, ft_strlen(&s[i]));
			break ;
		}
	}
	splitted[index] = NULL;
	return (splitted);
}
