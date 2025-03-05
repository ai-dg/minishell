/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:02:26 by ls                #+#    #+#             */
/*   Updated: 2024/06/15 12:44:31 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	go_home(t_shell_data *shell)
{
	char	*home;
	char	*path;
	int		i;
	int		exit;

	path = getcwd(NULL, 0);
	exit = 0;
	if (is_duplicate_key(shell->env, "HOME"))
		home = get_value_from_key(shell->env, "HOME");
	else
	{
		error_msg("minishell: cd: HOME not set\n");
		return (free_variable((void **)&path), shell->exit_status = 1, 1);
	}
	printf("%s\n", home);
	i = chdir(home);
	set_env_pwd(shell, path, home);
	if (i < 0)
		exit = 1;
	return (free_variable((void **)&path), shell->exit_status = exit, exit);
}
