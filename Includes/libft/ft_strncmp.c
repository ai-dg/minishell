/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:17:04 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/28 07:22:32 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	are_strings_valid(const char *s1, const char *s2, int *status)
{
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == NULL && s2 == NULL)
			*status = 0;
		else if (s1 == NULL)
			*status = -1;
		else
			*status = 1;
		return (false);
	}
	return (true);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	unsigned char	*str1;
	unsigned char	*str2;
	int				status;

	status = 0;
	if (!are_strings_valid(s1, s2, &status))
		return (status);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	count = 0;
	if (n < 1)
		return (0);
	while ((str1[count] || str2[count]) && count < n)
	{
		if (str1[count] != str2[count])
			return (str1[count] - str2[count]);
		count++;
	}
	return (0);
}

int	ft_strncmp_backward(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				len1;
	int				len2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	len1 = (int)ft_strlen(s1) - 1;
	len2 = (int)ft_strlen(s2) - 1;
	if (n < 1)
		return (0);
	while (str1 != NULL && str2 != NULL && (str1[len1] || str2[len2]) && n--)
	{
		if (str1[len1] != str2[len2])
			return (str1[len1] - str2[len2]);
		if (len1 > -1)
			len1--;
		if (len2 > -1)
			len2--;
		if (len1 == 0 || len2 == 0)
			return (str1[len1] - str2[len2]);
	}
	return (0);
}

int	ft_strncmp_ignore_espaces(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	unsigned char	*str1;
	unsigned char	*str2;
	int				status;

	status = 0;
	if (!are_strings_valid(s1, s2, &status))
		return (status);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	count = 0;
	if (n < 1)
		return (0);
	while (str1[count] <= 32)
		count++;
	while ((str1[count] || str2[count]) && count < n)
	{
		if (str1[count] != str2[count])
			return (str1[count] - str2[count]);
		count++;
	}
	return (0);
}

int	ft_strncmp_backward_ignore_espaces(const char *s1, const char *s2, size_t n)
{
	size_t			len1;
	size_t			len2;
	size_t			count;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	len1 = ft_strlen(s1) - 1;
	len2 = ft_strlen(s2) - 1;
	count = 0;
	if (n < 1)
		return (0);
	while (str1[len1] == 32)
		len1--;
	while ((str1[len1] || str2[len2]) && count < n)
	{
		if (str1[len1] != str2[len2])
			return (str1[len1] - str2[len2]);
		len1--;
		len2--;
		count++;
	}
	return (0);
}
