/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 13:10:50 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	write_msg_in_script(char *line_number_str, t_cmd *pipes,
		t_shell_data *shell, int i)
{
	line_number_str = ft_itoa(shell->number_line + 1);
	write(STDERR_FILENO, shell->file_script, ft_strlen(shell->file_script));
	write(STDERR_FILENO, ": line ", 7);
	write(STDERR_FILENO, line_number_str, ft_strlen(line_number_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, pipes->path_infiles[i],
		strlen(pipes->path_infiles[i]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	free_variable((void **)&line_number_str);
}

static void	write_msg_normal_error(t_cmd *pipes, int i)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, pipes->path_infiles[i],
		ft_strlen(pipes->path_infiles[i]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
}

static int	handle_path_infiles(t_cmd *pipes, t_shell_data *shell, int *print)
{
	char	*line_number_str;
	int		i;

	line_number_str = NULL;
	i = 0;
	while (pipes->path_infiles != NULL && pipes->path_infiles[i])
	{
		errno = 0;
		shell->input = open(pipes->path_infiles[i], O_RDONLY);
		if (shell->input < 0 && *print == 1)
		{
			if (shell->in_script == true)
			{
				write_msg_in_script(line_number_str, pipes, shell, i);
			}
			else
			{
				write_msg_normal_error(pipes, i);
				errno = 0;
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

int	open_fd_input(t_cmd *pipes, t_shell_data *shell, int print)
{
	int	result;

	result = 0;
	if (pipes->path_infiles == NULL)
	{
		return (-2);
	}
	result = handle_path_infiles(pipes, shell, &print);
	if (result < 0)
		return (result);
	if (shell->input == 0)
		shell->input = -1;
	return (shell->input);
}
