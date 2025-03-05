/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:00:16 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 15:37:08 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static int	count_inset(const char *s1, const char *set)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s1[i])
	{
		if (is_in_set(s1[i], set))
			count++;
		if (!is_in_set(s1[i], set))
			break ;
		i++;
	}
	return (count);
}

static int	count_rinset(const char *s1, const char *set)
{
	int	rcount;
	int	i;

	rcount = 0;
	i = ft_strlen(s1) - 1;
	while (i != 0)
	{
		if (is_in_set(s1[i], set))
			rcount++;
		if (!is_in_set(s1[i], set))
			break ;
		i--;
	}
	return (rcount);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	out;
	size_t	in;
	char	*trimmed;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	in = (size_t)count_inset(s1, set);
	out = (size_t)count_rinset(s1, set);
	if (in + out >= ft_strlen(s1))
		return (ft_strdup(""));
	len = ft_strlen(s1) - in - out;
	trimmed = ft_substr(s1, in, len);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
