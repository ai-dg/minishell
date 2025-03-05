/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:02:26 by ls                #+#    #+#             */
/*   Updated: 2024/06/22 14:30:03 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	backward_cd(t_shell_data *shell, char *path)
{
	char	*old;
	int		i;
	int		exit;

	path = getcwd(NULL, 0);
	if (!path)
		if (is_duplicate_key(shell->env, "PWD"))
			path = ft_strdup(get_value_from_key(shell->env, "PWD"));
	exit = 0;
	if (is_duplicate_key(shell->env, "OLDPWD"))
		old = get_value_from_key(shell->env, "OLDPWD");
	else
	{
		error_msg("minishell: cd: OLDPWD not set\n");
		return (free_variable((void **)&path), shell->exit_status = 1, 1);
	}
	if (!path_exist(old, NULL))
		return (handle_cd_file_error(shell, old));
	printf("%s\n", old);
	i = chdir(old);
	set_env_pwd(shell, path, old);
	if (i < 0)
		exit = 1;
	return (free_variable((void **)&path), shell->exit_status = exit, exit);
}

char	*get_path(char *inst)
{
	char	*path;

	path = NULL;
	if (ft_strncmp(inst, "/", 1) == 0 && ft_strlen(inst) == 1)
		path = ft_strdup("/");
	else if (ft_strncmp(inst, "//", 2) == 0 && ft_strlen(inst) == 2)
		path = ft_strdup("//");
	else if (ft_strncmp(inst, "/", 1) == 0 && ft_strlen(inst) > 2
		&& is_single_char_in_string(inst, "\\"))
		path = ft_strdup("/");
	else
		path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	return (path);
}

bool	handle_error_cd_messages(char *home, char **inst, t_shell_data *shell)
{
	if (inst[1] && ft_strlen(inst[1]) > 2 && ft_strncmp(inst[1], "--", 2) == 0)
	{
		error_msg("minishell: cd: --: invalid option\n");
		return (shell->exit_status = 2, true);
	}
	else if (inst[1] && ft_strlen(inst[1]) == 0 && !home)
	{
		error_msg("minishell: cd: HOME not set\n");
		return (shell->exit_status = 1, true);
	}
	else if (!inst[1])
	{
		if (!home)
		{
			error_msg("minishell: cd: HOME not set\n");
			return (shell->exit_status = 1, true);
		}
		else if (ft_strlen(home) == 0)
			return ((shell->exit_status = 0, true));
	}
	return (false);
}

bool	handle_process_cd(char **inst, char *old, t_shell_data *shell, int *i)
{
	char	*path;

	path = NULL;
	if (inst[1] && ft_strlen(inst[1]) == 1 && inst[1][0] == '-')
		return (backward_cd(shell, inst[1]), true);
	if (inst[1] && ft_strlen(inst[1]) == 2 && ft_strncmp(inst[1], "--", 2) == 0)
		return (go_home(shell), true);
	if (inst[1] && !is_dir("chdir: ", false) && !path_exist(inst[1], old))
	{
		shell->cd_error++;
		if (shell->cd_error > 1)
			return (back_to_safe_directory(shell), true);
		if ((ft_strncmp_backward(old, "/..", 3) != 0))
		{
			path = ft_fstrjoin(old, "/..", NONE);
			change_env_value(shell->env, "PWD", path);
			free_variable((void **)&path);
		}
		return (shell->exit_status = 1, true);
	}
	else if (inst[1] && ft_count_args(inst) <= 2
		&& !is_single_char_in_string(inst[1], " "))
		*i = chdir(formated_path(shell, &inst[1]));
	return (false);
}

int	cd_m(t_shell_data *shell, char **inst)
{
	int		i;
	char	*home;
	char	*path;
	char	*old;

	i = 0;
	old = get_value_from_key(shell->env, "PWD");
	home = get_value_from_key(shell->env, "HOME");
	if (handle_error_cd_messages(home, inst, shell))
		return (shell->exit_status);
	if (!inst[1])
		i = chdir(home);
	else if (ft_count_args(inst) > 2)
		i = -1;
	else if (handle_process_cd(inst, old, shell, &i))
		return (shell->exit_status);
	path = get_path(inst[1]);
	if (!path)
		return (shell->exit_status = 1, -1);
	set_env_pwd(shell, old, path);
	if (i == -1)
		handle_cd_args_error(shell, inst);
	else
		shell->exit_status = 0;
	return (free_variable((void **)&path), shell->exit_status);
}
