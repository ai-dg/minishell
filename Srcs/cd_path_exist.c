/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:02:26 by ls                #+#    #+#             */
/*   Updated: 2024/07/01 11:58:21 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*formated_path(t_shell_data *shell, char **inst)
{
	char	*cd_path;

	if (!inst)
		return (NULL);
	cd_path = get_value_from_key(shell->env, "CDPATH");
	if (!cd_path && ft_strlen(cd_path) == 0)
		return (*inst);
	else
		*inst = ft_fstrjoin(cd_path, *inst, SECOND);
	return (*inst);
}

void	set_env_pwd(t_shell_data *shell, char *old_pwd, char *new_pwd)
{
	char	*temp_old;
	char	*temp_new;

	temp_old = ft_strdup(old_pwd);
	temp_new = ft_strdup(new_pwd);
	if (temp_old)
		update_env(shell->env, "OLDPWD", temp_old, shell);
	if (temp_new)
		update_env(shell->env, "PWD", temp_new, shell);
	free_variable((void **)&temp_old);
	free_variable((void **)&temp_new);
}

bool	is_dir(char *ctx, bool silent)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (!silent)
		{
			if (ctx)
				error_msg(ctx);
			error_msg("error retrieving current directory");
			error_msg(": getcwd: cannot access parent directories: ");
			error_msg("No such file or directory\n");
		}
		return (false);
	}
	else
		free_variable((void **)&cwd);
	return (true);
}

bool	check_parent(char *path)
{
	char	**splitted_path;
	int		args;
	char	*to_test;
	bool	exist;
	DIR		*dir;

	if (!path)
		return (false);
	splitted_path = ft_split(path, '/');
	if (!splitted_path)
		return (false);
	args = ft_count_args(splitted_path);
	args--;
	to_test = ft_join_nsplitted(splitted_path, "/", args);
	to_test = ft_fstrjoin("/", to_test, SECOND);
	dir = opendir(to_test);
	exist = safe_check_and_close_dir(dir);
	free_array(&splitted_path);
	free_variable((void **)&to_test);
	return (exist);
}

bool	path_exist(char *path, char *old)
{
	DIR		*dir;
	bool	exist;

	if (ft_strncmp("..", path, ft_strlen(path)) == 0)
		return (check_parent(old));
	exist = false;
	dir = opendir(path);
	exist = safe_check_and_close_dir(dir);
	return (exist);
}
