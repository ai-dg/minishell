/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:47:29 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 16:14:34 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*check_git(char *line)
{
	char	*git;

	git = get_git_prompt();
	if (git)
	{
		line = ft_fstrjoin(line, "(", FIRST);
		line = ft_fstrjoin(line, BOLD_RED, FIRST);
		line = ft_fstrjoin(line, git, BOTH);
		line = ft_fstrjoin(line, BOLD_BLUE, FIRST);
		line = ft_fstrjoin(line, ")", FIRST);
	}
	return (line);
}

char	*get_parent_path(char **dirs, int args)
{
	int		i;
	char	*new_path;

	new_path = NULL;
	i = 0;
	while (dirs[i] && i < args)
	{
		new_path = ft_fstrjoin(new_path, "/", FIRST);
		new_path = ft_fstrjoin(new_path, dirs[i], FIRST);
		i++;
	}
	new_path = ft_fstrjoin(new_path, "/.git/HEAD", FIRST);
	return (new_path);
}

int	get_fd_git(char *path)
{
	int		fd;
	int		sub_dirs;
	char	**paths;
	char	*tmp;

	paths = ft_split(path, '/');
	sub_dirs = ft_count_args(paths);
	fd = -1;
	while (sub_dirs >= 0)
	{
		tmp = get_parent_path(paths, sub_dirs);
		fd = open(tmp, O_RDONLY, 0666);
		free_variable((void **)&tmp);
		sub_dirs--;
		if (fd > -1)
			return (free_array(&paths), fd);
	}
	return (free_array(&paths), -1);
}

char	*get_git_prompt(void)
{
	int		fd;
	char	*branch;
	char	**div;
	int		i;
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	fd = get_fd_git(path);
	if (fd < 0)
		return (free(path), NULL);
	i = 0;
	branch = get_next_line(fd);
	div = ft_split(branch, '/');
	if (!div)
		return (free(path), close(fd), NULL);
	while (div[i])
		i++;
	free_variable((void **)&branch);
	branch = ft_strdup(div[i - 1]);
	branch[ft_strlen(branch) - 1] = '\0';
	free_array(&div);
	free_variable((void **)&path);
	return (close(fd), branch);
}
