/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:35:41 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/12 17:29:15 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include "./Includes/minishell.sh"

static char	*trim(char *s, char c, int d)
{
	if (d <= 0)
		while (*s && *s != c)
			s++;
	if (d > 0)
		while (*s && *s == c)
			s++;
	return (s);
}

size_t	count_word(char const *s, char c)
{
	size_t	word;
	char	*str;

	str = (char *)s;
	if (!str)
		return (0);
	word = 0;
	while (*str)
	{
		str = trim(str, c, 1);
		if (*str)
			word++;
		str = trim(str, c, -1);
	}
	return (word);
}

static size_t	get_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	size_t	index;
	int		i;

	i = 0;
	index = 0;
	splitted = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!splitted || !s)
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] == c)
			s++;
		if (s[i] && s[i] != c)
		{
			splitted[index++] = ft_substr(&s[i], 0, get_len(&s[i], c));
			i += get_len(&s[i], c);
		}
	}
	splitted[index] = NULL;
	return (splitted);
}

char	*ft_join_nsplitted(char **splitted, char *c, int n)
{
	int		i;
	int		length;
	char	*joined;

	length = 0;
	i = 0;
	while (splitted[i] && i < n)
	{
		length += (int)ft_strlen(splitted[i]) + 1;
		i++;
	}
	joined = malloc((length + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	reset_buf(joined, length + 1);
	i = 0;
	while (splitted[i])
	{
		joined = ft_fstrjoin(joined, splitted[i], FIRST);
		if (i < n)
			joined = ft_fstrjoin(joined, c, FIRST);
		i++;
	}
	joined[length - 1] = 0;
	return (joined);
}
