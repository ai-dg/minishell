/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_session.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:03:55 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 11:25:49 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	set_session(t_shell_data *shell)
{
	shell->session = NULL;
	return (0);
}

static void	assign_env_to_session(t_shell_data *shell, char **keyval)
{
	if (shell->session)
	{
		if (!is_duplicate_key(shell->session, keyval[0]))
			push_back_env_node(&shell->session, new_env_node(keyval[0],
					keyval[1], shell));
		else
			change_env_value(shell->session, keyval[0], keyval[1]);
	}
	else
		shell->session = new_env_node(keyval[0], keyval[1], shell);
}

int	add_session(t_shell_data *shell, char **inst)
{
	char	**keyval;
	char	*arg;

	keyval = NULL;
	if (inst == NULL)
		return (shell->exit_status = 1, 1);
	arg = ft_strdup(inst[0]);
	if (!arg)
		return (shell->exit_status = 1, 1);
	keyval = ft_split_key_val(arg, '=');
	if (!keyval)
		return (shell->exit_status = 1, free_variable((void **)&arg), -1);
	if (!is_valid_variable(keyval[0]))
	{
		print_error(arg, ": command not found\n", shell);
		return (free_variable((void **)&arg), free_array(&keyval),
			shell->exit_status = 127, 127);
	}
	if (is_duplicate_key(shell->env, keyval[0]))
		return (free_variable((void **)&arg), export_m(shell, inst),
			shell->exit_status = 0, free_array(&keyval), 0);
	assign_env_to_session(shell, keyval);
	return (free_array(&keyval), free_variable((void **)&arg), 0);
}

int	session_to_env(t_shell_data *shell, char *key)
{
	push_back_env_node(&shell->env, extract_node_with_key(&shell->session, key,
			EXTRACT));
	return (0);
}

int	handle_export_options(t_shell_data *shell, char **inst)
{
	char	err[3];

	ft_reset_buffer(err, 3);
	if (inst[1] && ft_strlen(inst[1]) > 0)
		err[0] = inst[1][0];
	if (inst[1] && ft_strlen(inst[1]) > 1)
		err[1] = inst[1][1];
	if (ft_strncmp(inst[1], "-", 1) == 0)
	{
		shell->exit_status = 2;
		print_error(err, ": invalid option\n", shell);
		return (1);
	}
	return (0);
}
