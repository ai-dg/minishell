/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:19:16 by ls                #+#    #+#             */
/*   Updated: 2024/06/13 19:23:16 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_home_path_alt(void)
{
	char	*home_path;
	char	*user;

	home_path = NULL;
	user = NULL;
	user = getenv("USER");
	if (!user)
		return (NULL);
	home_path = ft_fstrjoin("/home/", user, NONE);
	return (home_path);
	return (NULL);
}

char	*get_home_path(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		home = get_home_path_alt();
	if (!home)
		return (ft_strdup("./"));
	return (ft_strdup(home));
}

char	*get_login(void)
{
	DIR				*dir;
	struct dirent	*directory;

	dir = opendir("/home");
	directory = readdir(dir);
	while (directory)
	{
		if (directory->d_name[0] != '.' && access(directory->d_name, X_OK))
		{
			closedir(dir);
			return (ft_strdup(directory->d_name));
		}
		directory = readdir(dir);
	}
	closedir(dir);
	return (ft_strdup("???"));
}
