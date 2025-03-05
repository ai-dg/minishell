/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:37:45 by ls                #+#    #+#             */
/*   Updated: 2024/06/10 14:13:56 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_min_size(size_t size1, size_t size2)
{
	if (size1 < size2)
	{
		return (size1);
	}
	return (size2);
}

static void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		return (NULL);
	}
	return (ptr);
}

static void	*realloc_memory(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;
	size_t	min_size;

	new_ptr = safe_malloc(new_size);
	if (!new_ptr)
	{
		return (NULL);
	}
	min_size = get_min_size(old_size, new_size);
	ft_memcpy(new_ptr, ptr, min_size);
	free(ptr);
	return (new_ptr);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	size_t	old_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		return (safe_malloc(new_size));
	}
	old_size = strlen((char *)ptr) + 1;
	return (realloc_memory(ptr, new_size, old_size));
}
