/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:10:53 by ls                #+#    #+#             */
/*   Updated: 2024/06/12 16:17:53 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cpy(char *src, char *dest)
{
	while (*src)
		*dest++ = *src++;
	return (dest);
}

static int	mode_free_checker(char *s1, int freemode)
{
	if (!s1 && freemode == SECOND)
		return (BOTH);
	if (!s1 && freemode == NONE)
		return (FIRST);
	return (freemode);
}

static void	free_chars(char *s1, char *s2, int freemode)
{
	if (freemode == NONE)
		return ;
	if (freemode == FIRST)
	{
		free_variable((void **)&s1);
		s1 = NULL;
	}
	if (freemode == SECOND)
	{
		free_variable((void **)&s2);
		s2 = NULL;
	}
	if (freemode == BOTH)
	{
		free_variable((void **)&s1);
		free_variable((void **)&s2);
		s1 = NULL;
		s2 = NULL;
	}
}

// static void free_chars(char **s1, char **s2, int freemode) {
//     if (freemode == NONE) return ;
//     if ((freemode == FIRST || freemode == BOTH) && s1 && *s1) {
//         free(*s1);
//         *s1 = NULL;
//     }
//     if ((freemode == SECOND || freemode == BOTH) && s2 && *s2) {
//         free(*s2);
//         *s2 = NULL;
//     }
// }

static char	*get_void_char(void)
{
	char	*res;

	res = malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_fstrjoin(char *s1, char *s2, int freemode)
{
	char	*new;
	char	*tmp;
	int		t_len;

	new = NULL;
	tmp = NULL;
	t_len = 0;
	if (!s2)
		return (free_chars(s1, s2, freemode), NULL);
	if (!s1)
		freemode = mode_free_checker(s1, freemode);
	if (!s1)
		s1 = get_void_char();
	t_len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (t_len < 1)
		return (free_chars(s1, s2, freemode), get_void_char());
	new = malloc(sizeof(char) * (t_len + 2));
	ft_bzero(new, (size_t)t_len + 2);
	if (!new)
		return (free_chars(s1, s2, freemode), NULL);
	tmp = cpy(s1, new);
	ft_strcpy(tmp, s2);
	free_chars(s1, s2, freemode);
	return (new);
}

// char *ft_fstrjoin(char *s1, char *s2, int freemode) {
//     if (!s2) return (NULL);

//     int len1 = s1 ? strlen(s1) : 0;
//     int len2 = strlen(s2);
//     char *new_str = malloc(len1 + len2 + 1);
//     if (!new_str) {
//         free_chars(&s1, &s2, freemode);
//         return (NULL);
//     }

//     // Copy strings into new_str
//     if (s1) strcpy(new_str, s1);
//     strcpy(new_str + len1, s2);

//     free_chars(&s1, &s2, freemode);

//     return (new_str);
// }
