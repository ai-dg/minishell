/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 17:14:40 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static bool	if_output_redir_is_final(t_cmd *pipe, t_shell_data *shell)
{
	t_token	*current;
	int		i;
	int		pos1;
	int		pos2;

	(void)shell;
	current = pipe->tokens;
	i = 0;
	pos1 = 0;
	pos2 = 0;
	while (current)
	{
		if (current->type == REDIR_OUT)
			pos1 = i;
		else if (current->type == APPEND_REDIR_OUT)
			pos2 = i;
		i++;
		current = current->next;
	}
	if (pos1 > pos2)
		return (true);
	else if (pos1 < pos2)
		return (false);
	return (true);
}

static int	handle_path_outfiles(t_cmd *pipe, int *output_redir)
{
	int	i;

	i = 0;
	while (pipe->path_outfiles != NULL && pipe->path_outfiles[i])
	{
		errno = 0;
		*output_redir = open(pipe->path_outfiles[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*output_redir < 0)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, pipe->path_outfiles[i],
				ft_strlen(pipe->path_outfiles[i]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			errno = 0;
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	handle_path_append_outfiles(t_cmd *pipe, int *output_append)
{
	int	i;

	i = 0;
	while (pipe->path_append_outfiles != NULL && pipe->path_append_outfiles[i])
	{
		errno = 0;
		*output_append = open(pipe->path_append_outfiles[i],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (*output_append < 0)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, pipe->path_append_outfiles[i],
				ft_strlen(pipe->path_append_outfiles[i]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			errno = 0;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	open_fd_output(t_cmd *pipe, t_shell_data *shell)
{
	int	output_redir;
	int	output_append;
	int	result;

	if (pipe->path_outfiles == NULL && pipe->path_append_outfiles == NULL)
	{
		shell->output = STDOUT_FILENO;
		return (-2);
	}
	output_redir = 0;
	output_append = 0;
	result = 0;
	result = handle_path_outfiles(pipe, &output_redir);
	if (result < 0)
		return (result);
	result = handle_path_append_outfiles(pipe, &output_append);
	if (result < 0)
		return (result);
	if (if_output_redir_is_final(pipe, shell))
		shell->output = output_redir;
	else
		shell->output = output_append;
	return (shell->output);
}
