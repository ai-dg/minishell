/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:08:14 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	bad_pwd_options(t_shell_data *shell, char **inst)
{
	(void)shell;
	if (inst[1])
	{
		if (is_single_char_in_string(inst[1], "-"))
			return (false);
		if (ft_strncmp(inst[1], "-", 1) == 0)
			return (true);
	}
	return (false);
}

static void	open_fd_output_pwd(t_shell_data *shell, bool *write_in_fd,
		int *fd_output, int *fd_input)
{
	if (shell->total_pipes == 1)
	{
		if (shell->pipe->path_outfiles || shell->pipe->path_append_outfiles)
		{
			*write_in_fd = true;
			*fd_output = open_fd_output(shell->pipe, shell);
		}
		if (shell->pipe->path_infiles)
		{
			*fd_input = open_fd_input(shell->pipe, shell, 1);
		}
	}
}

static void	write_error_pwd_msg(char **inst, int fd_output)
{
	ft_putstr_fd("minishell: pwd: ", fd_output);
	ft_putstr_fd(inst[1], fd_output);
	ft_putstr_fd(": invalid option\n", fd_output);
}

static void	write_buff_and_free(t_shell_data *shell, int *fd_output,
		bool *write_in_fd)
{
	char	*buff;

	buff = malloc(255);
	if (!buff)
		exit_1_malloc(&shell);
	ft_reset_buffer(buff, 255);
	getcwd(buff, 255);
	if (!buff || ft_strlen(buff) == 0)
	{
		ft_fprintf(stderr, "pwd: error retrieving current directory: getcwd: ");
		ft_fprintf(stderr, "cannot access parent directories: ");
		ft_fprintf(stderr, "No such file or directory\n");
		shell->exit_status = 1;
	}
	else if (*write_in_fd == true)
	{
		ft_putstr_fd(buff, *fd_output);
		ft_putstr_fd("\n", *fd_output);
	}
	else
		printf("%s\n", buff);
	free_variable((void **)&buff);
}

int	pwd_m(t_shell_data *shell, char **inst)
{
	bool	write_in_fd;
	int		fd_output;
	int		fd_input;

	write_in_fd = false;
	fd_output = 0;
	fd_input = 0;
	shell->exit_status = 0;
	open_fd_output_pwd(shell, &write_in_fd, &fd_output, &fd_input);
	if (write_in_fd == true && fd_output == -1 && shell->total_pipes == 1)
		return (shell->exit_status = 1);
	if (fd_input == -1 && shell->total_pipes == 1)
		return (shell->exit_status = 1);
	if (bad_pwd_options(shell, inst))
	{
		if (write_in_fd == true)
			return (write_error_pwd_msg(inst, fd_output),
				shell->exit_status = 2, 2);
		else
			return (write_error_pwd_msg(inst, 2), shell->exit_status = 2, 2);
	}
	write_buff_and_free(shell, &fd_output, &write_in_fd);
	return (0);
}
