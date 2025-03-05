/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_affectation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:11:23 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	only_affectation(t_cmd *pipe)
{
	t_cmd	*current;
	t_token	*token;

	current = pipe;
	token = pipe->tokens;
	if (current->next)
		return (false);
	while (token)
	{
		if (token->type != VARIABLE)
			return (false);
		token = token->next;
	}
	return (true);
}

char	**get_chars_from_single(char *aff, t_shell_data *shell)
{
	char	**inst;

	inst = malloc(sizeof(char *) * 2);
	if (!inst)
		exit_1_malloc(&shell);
	inst[0] = ft_strdup(aff);
	inst[1] = NULL;
	return (inst);
}

int	exec_affectations(t_shell_data *shell)
{
	t_token	*token;
	char	**args;

	args = NULL;
	token = shell->pipe->tokens;
	while (token)
	{
		add_session(shell, args);
		free_array(&args);
		args = NULL;
		token = token->next;
	}
	return (0);
}

int	var_affectations(t_shell_data *shell)
{
	t_token	*token;

	token = shell->pipe->tokens;
	if (token && only_affectation(shell->pipe))
		exec_affectations(shell);
	return (0);
}
