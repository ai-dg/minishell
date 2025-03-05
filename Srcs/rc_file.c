/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:39:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 11:32:02 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	process_file(int fd, char *line, t_shell_data *shell)
{
	while (line)
	{
		if (ft_strlen(line) == 0 || line[0] == '\n')
			ft_drop();
		else
		{
			shell->prompt = ft_strdup(line);
			execute_commands(shell);
		}
		free_variable((void **)&line);
		line = get_next_line(fd);
	}
}

void	init_rc_file(t_shell_data *shell)
{
	char	*home;
	char	*path;
	int		fd;
	char	*line;

	home = get_home_path();
	path = ft_fstrjoin(home, "/.minishellrc", NONE);
	free_variable((void **)&home);
	fd = open(path, O_CREAT | O_RDONLY, 0666);
	if (fd < 0)
	{
		close(fd);
		return ;
	}
	line = get_next_line(fd);
	process_file(fd, line, shell);
	close(fd);
	free_variable((void **)&path);
}
