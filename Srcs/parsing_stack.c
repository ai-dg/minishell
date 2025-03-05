/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/30 17:13:00 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

size_t	ft_strlen_alt(const char *s)
{
	size_t	size;

	if (s == NULL)
		return (0);
	size = 0;
	while (s[size] && ft_isprint(s[size]))
		size++;
	return (size);
}

static void	count_pipes(t_shell_data *shell, int *j, int *cmd)
{
	while (shell->initial_parsed[*j])
	{
		if (ft_strcmp(shell->initial_parsed[*j], "|") == 0)
			(*cmd)++;
		(*j)++;
	}
}

static void	fill_pipes_in_shell(t_shell_data *shell, t_token *token, int *i)
{
	t_cmd	*first;
	t_cmd	*temp;

	temp = NULL;
	first = shell->pipe;
	while (shell->initial_parsed[*i])
	{
		if (ft_strcmp(shell->initial_parsed[*i], "|") == 0)
		{
			shell->pipe->next = new_cmd_node(token, shell);
			temp = shell->pipe;
			shell->pipe = shell->pipe->next;
			shell->pipe->prev = temp;
			(*i)++;
		}
		if (!shell->initial_parsed[*i])
			break ;
		parentheses_traitement(shell->initial_parsed, shell->pipe, i, shell);
		shell->pipe->tokens = push_token(shell->pipe->tokens,
				shell->initial_parsed[*i], shell);
		(*i)++;
	}
	shell->pipe->next = NULL;
	shell->pipe = first;
}

static bool	condition_to_go_out(t_shell_data *shell)
{
	return (ft_count_args(shell->initial_parsed) == 1
		&& ft_strlen(shell->initial_parsed[0]) == 1
		&& !(ft_isprint(shell->initial_parsed[0][0]))
		&& shell->initial_parsed[0][0] != '\0');
}

int	args_parsed_to_stack(t_shell_data *shell)
{
	t_token	*token;
	int		i;
	int		j;
	int		cmd;

	i = 0;
	j = 0;
	cmd = 0;
	token = NULL;
	if (!shell->initial_parsed || !shell->initial_parsed[0])
		return (-1);
	if (condition_to_go_out(shell))
	{
		print_error(shell->initial_parsed[0], " :command not found\n", shell);
		return (shell->exit_status = 127, -1);
	}
	count_pipes(shell, &j, &cmd);
	shell->pipe = new_cmd_node(token, shell);
	if (!shell->pipe)
		return (-1);
	fill_pipes_in_shell(shell, token, &i);
	double_to_char(shell->pipe, shell);
	if (shell->initial_parsed)
		free_array(&shell->initial_parsed);
	return (0);
}
