/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getuid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:26:15 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 10:30:55 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	ft_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

char	*ft_getuid(void)
{
	DIR				*check;
	struct dirent	*into_dir;
	char			*uid;

	uid = NULL;
	check = opendir("/run/systemd/users/");
	into_dir = readdir(check);
	while (into_dir && !ft_only_digits(into_dir->d_name))
		into_dir = readdir(check);
	uid = ft_strdup(into_dir->d_name);
	closedir(check);
	return (uid);
}
