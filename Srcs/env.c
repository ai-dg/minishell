/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:57:26 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 12:38:07 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	init_env_from_sys_env(t_shell_data *shell, t_env **env)
{
	int		i;
	char	**keyval;
	t_env	*new_node;

	i = 0;
	keyval = NULL;
	new_node = NULL;
	while (shell->sys_env[i])
	{
		keyval = ft_split_key_val(shell->sys_env[i], '=');
		if (!keyval)
			return (free_t_env(env), -1);
		new_node = new_env_node(keyval[0], keyval[1], shell);
		if (!new_node)
			return (free_array(&keyval), free_t_env(env), -1);
		if (i == 0)
			*env = new_node;
		else
			push_back_env_node(env, new_node);
		free_array(&keyval);
		i++;
	}
	return (0);
}

int	set_env(t_shell_data *shell)
{
	t_env	*env;

	env = NULL;
	if (ft_count_args(shell->sys_env) == 0)
	{
		env = set_minimal_env(shell);
	}
	else
	{
		if (init_env_from_sys_env(shell, &env) != 0)
		{
			return (-1);
		}
	}
	shell->env = env;
	change_value_in_env(&shell->env, "SHLVL", ft_itoa(shell->shell_level));
	return (0);
}

static void	find_env(t_shell_data *shell, char **inst, int *i, int *j)
{
	while (inst[*j])
	{
		if (ft_strcmp(inst[*j], "env") != 0 && inst[*i])
			shell->in_env_cmd = true;
		(*j)++;
	}
}

static void	find_path_final(t_shell_data *shell, char **inst, char *path_final)
{
	if (shell->in_env_cmd == true && shell->just_one_pipe == false)
	{
		remove_env_arg(inst);
		check_cmd_access_final_path(inst, path_final, shell);
	}
	else if (shell->in_env_cmd == true && shell->just_one_pipe == true)
	{
		remove_env_arg(inst);
		shell->exit_status = pipex(shell->pipe, shell);
		shell->in_env_cmd = false;
	}
}

int	env_m(t_shell_data *shell, char **inst)
{
	int		i;
	bool	exec;
	char	*path_final;
	int		j;

	(void)inst;
	i = 0;
	exec = true;
	path_final = NULL;
	j = 0;
	find_env(shell, inst, &i, &j);
	find_path_final(shell, inst, path_final);
	while (inst[i])
	{
		if (!(ft_strncmp(inst[i], "env", ft_strlen(inst[i])) == 0)
			|| ft_strlen(inst[i]) != 3)
			exec = false;
		i++;
	}
	if (exec == true)
	{
		print_env_list(NULL, shell->env, inst, true);
		return (0);
	}
	return (127);
}
