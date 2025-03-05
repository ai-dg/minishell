/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path_exist_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:02:26 by ls                #+#    #+#             */
/*   Updated: 2024/06/24 07:28:29 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	back_to_safe_directory(t_shell_data *shell)
{
	shell->cd_error = 0;
	return (shell->exit_status = 0, chdir(get_value_from_key(shell->env,
				"OLDPWD")));
}

int	handle_cd_args_error(t_shell_data *shell, char **inst)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, inst[0], ft_strlen(inst[0]));
	write(2, ": ", 2);
	if (ft_count_args(inst) > 2)
		write(2, "too many arguments\n", ft_strlen("too many arguments\n"));
	else
		perror("");
	return (shell->exit_status = 1, 1);
}

int	handle_cd_file_error(t_shell_data *shell, char *path)
{
	error_msg("minishell: cd: ");
	error_msg(path);
	error_msg(": Aucun fichier ou dossier de ce nom\n");
	return (free_variable((void **)&path), shell->exit_status = 1, 1);
}

/**
 * 	@brief commande cd
 *  ajouter la gestion des liens symboliques et de root *
 */
void	update_env(t_env *env, char *key, char *val, t_shell_data *shell)
{
	if (val)
	{
		if (is_duplicate_key(env, key))
			change_env_value(env, key, val);
		else
			push_back_env_node(&env, new_env_node(key, val, shell));
	}
}

bool	safe_check_and_close_dir(DIR *dir)
{
	if (dir == NULL)
		return (false);
	closedir(dir);
	return (true);
}
