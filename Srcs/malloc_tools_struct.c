/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:13:24 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/27 15:25:58 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	free_t_env(t_env **head)
{
	t_env	*current;
	t_env	*next;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		current->key = NULL;
		if (current->value != NULL)
		{
			free(current->value);
			current->value = NULL;
		}
		ft_bzero(current, sizeof(t_env));
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_t_fds(t_fds **head)
{
	t_fds	*current;
	t_fds	*next;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free_variable((void **)&current->input);
		free_variable((void **)&current->output);
		ft_bzero(current, sizeof(t_fds));
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_t_pipefd(t_pipefd **head)
{
	t_pipefd	*current;
	t_pipefd	*next;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free_variable((void **)&current->values);
		ft_bzero(current, sizeof(t_pipefd));
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_tokens(t_cmd *pipe)
{
	t_token	*token;
	t_token	*next_token;

	token = pipe->tokens;
	while (token)
	{
		next_token = token->next;
		free_variable((void **)&token->value);
		ft_bzero(token, sizeof(t_token));
		free_variable((void **)&token);
		token = next_token;
	}
}

void	free_cmd_pipe(t_shell_data *shell)
{
	t_cmd	*next_cmd;
	t_cmd	*pipe;

	if (shell == NULL && shell->pipe == NULL)
		return ;
	pipe = shell->pipe;
	while (pipe)
	{
		next_cmd = pipe->next;
		free_variable((void **)&pipe->cmd);
		free_array(&pipe->args);
		free_variable((void **)&pipe->delimiter);
		free_array(&pipe->path_infiles);
		free_array(&pipe->path_outfiles);
		free_array(&pipe->path_append_outfiles);
		free_array(&pipe->delimiter_var);
		free_array(&pipe->variables);
		free_variable((void **)&pipe->p_execute);
		free_tokens(pipe);
		ft_bzero(pipe, sizeof(t_cmd));
		free_variable((void **)&pipe);
		pipe = next_cmd;
	}
	shell->pipe = NULL;
}
