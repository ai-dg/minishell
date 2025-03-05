/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fileno.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:39:38 by ls                #+#    #+#             */
/*   Updated: 2024/06/14 08:04:04 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fileno(FILE *stream)
{
	if (stream == stdin)
	{
		return (STDIN_FILENO);
	}
	else if (stream == stdout)
	{
		return (STDOUT_FILENO);
	}
	else if (stream == stderr)
	{
		return (STDERR_FILENO);
	}
	else
	{
		return (stream->_fileno);
	}
}
