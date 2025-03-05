/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:05:30 by ls                #+#    #+#             */
/*   Updated: 2024/07/01 14:34:57 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	unset_errors(char *inst, t_shell_data *shell)
{
	if (inst[0] == '-')
	{
		write(STDERR_FILENO, "minishell: unset: `", 19);
		write(STDERR_FILENO, inst, 2);
		write(STDERR_FILENO, "': invalid option\n", 18);
		shell->exit_status = 2;
		return (true);
	}
	else if (!is_valid_variable(inst))
	{
		write(STDERR_FILENO, "minishell: unset: `", 19);
		write(STDERR_FILENO, inst, ft_strlen(inst));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		shell->exit_status = 1;
		return (true);
	}
	else
		shell->exit_status = 0;
	return (false);
}

void	change_value_in_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			break ;
		}
		tmp = tmp->next;
	}
	free_variable((void **)&value);
}

void	unset_variable(t_shell_data *shell, char **inst, int i)
{
	if (shell->env)
		if (inst[i] && is_duplicate_key(shell->env, inst[i]))
			extract_node_with_key(&shell->env, inst[i], DELETE);
	if (shell->session)
		if (inst[i] && is_duplicate_key(shell->session, inst[i]))
			extract_node_with_key(&shell->session, inst[i], DELETE);
}

int	unset_m(t_shell_data *shell, char **inst)
{
	int		i;
	char	*to_change;

	i = 1;
	shell->exit_status = 0;
	while (inst[i])
	{
		if (unset_errors(inst[i], shell))
			ft_drop();
		else
		{
			if (shell->sys_env[0] == NULL && ft_strcmp(inst[i], "PATH") == 0)
			{
				to_change = ft_strdup("/bin/env");
				change_value_in_env(&shell->env, "_", to_change);
			}
			unset_variable(shell, inst, i);
		}
		i++;
	}
	return (shell->exit_status);
}
