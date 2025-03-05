/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:04:44 by ls                #+#    #+#             */
/*   Updated: 2024/07/01 15:14:17 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*handle_indicators_and_quotes(char *buffer, t_shell_data *shell)
{
	char	indicator_double;
	char	*result;
	char	*indicator_ptr;

	indicator_double = 0x1F;
	result = (char *)malloc(ft_strlen(buffer) + 1);
	if (!result)
		exit_1_malloc(&shell);
	result[0] = '\0';
	indicator_ptr = ft_strchr(buffer, indicator_double);
	if (indicator_ptr)
	{
		ft_strlcat(result, buffer, indicator_ptr - buffer);
		ft_strcat(result, indicator_ptr + 1);
	}
	else
	{
		ft_strcpy(result, buffer);
	}
	return (result);
}

static void	initialize_values_to_null_echo(t_echo_values *values)
{
	values->i = 1;
	values->skip = false;
	values->ignore = false;
	values->write_in_fd = false;
	values->fd_output = 0;
	values->fd_input = 0;
}

static void	open_fd_echo(t_shell_data *shell, t_echo_values *values)
{
	if (shell->total_pipes == 1)
	{
		if (shell->pipe->path_outfiles || shell->pipe->path_append_outfiles)
		{
			values->write_in_fd = true;
			values->fd_output = open_fd_output(shell->pipe, shell);
		}
		if (shell->pipe->path_infiles)
		{
			values->fd_input = open_fd_input(shell->pipe, shell, 1);
		}
	}
}

static void	write_into_fd_or_stdout(t_echo_values *values, char **inst)
{
	while (inst[values->i])
	{
		if (inst[values->i] && ((ft_strncmp(inst[values->i], "-n", 2) == 0)
				&& is_single_char_in_string(&inst[values->i][1], "n"))
			&& values->ignore == false)
			values->skip = true;
		else
		{
			if (values->write_in_fd == true)
				write(values->fd_output, inst[values->i],
					ft_strlen(inst[values->i]));
			else
				write(1, inst[values->i], ft_strlen(inst[values->i]));
			if (inst[values->i + 1])
			{
				if (values->write_in_fd == true)
					write(values->fd_output, " ", 1);
				else
					write(1, " ", 1);
			}
			values->ignore = true;
		}
		values->i++;
	}
}

int	echo_m(t_shell_data *shell, char **inst)
{
	t_echo_values	values;

	shell->exit_status = 0;
	initialize_values_to_null_echo(&values);
	open_fd_echo(shell, &values);
	if (values.write_in_fd == true && values.fd_output == -1
		&& shell->total_pipes == 1)
		return (shell->exit_status = 1);
	if (values.fd_input == -1 && shell->total_pipes == 1)
		return (shell->exit_status = 1);
	write_into_fd_or_stdout(&values, inst);
	if (!values.skip)
	{
		if (values.write_in_fd == true)
			write(values.fd_output, "\n", 1);
		else
			write(1, "\n", 1);
	}
	if (values.write_in_fd == true)
		close(values.fd_output);
	return (shell->exit_status);
}
