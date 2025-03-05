/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:32:26 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	joint_str_final_path(char *tmp, char **cmd_args, int len_path_total)
{
	ft_strlcat(tmp, "/", 2);
	ft_strlcat(tmp, cmd_args[0], len_path_total - ft_strlen(tmp));
}

static void	increment_and_free(char *tmp, int *j)
{
	free_variable((void **)&tmp);
	(*j)++;
}

static char	*search_final_path(t_shell_data *shell, char **cmd_args)
{
	char	*path_final;
	char	*tmp;
	int		j;
	int		len_path_total;

	path_final = NULL;
	j = 0;
	while (shell->paths[j] != NULL)
	{
		len_path_total = ft_strlen(shell->paths[j]) + ft_strlen(cmd_args[0])
			+ 2;
		tmp = (char *)malloc(sizeof(char) * (len_path_total + 1));
		if (tmp == NULL)
			exit_1_malloc(&shell);
		ft_strlcpy(tmp, shell->paths[j], len_path_total);
		joint_str_final_path(tmp, cmd_args, len_path_total);
		if (access(tmp, X_OK) == 0)
		{
			path_final = ft_strdup(tmp);
			free_variable((void **)&tmp);
			break ;
		}
		increment_and_free(tmp, &j);
	}
	return (path_final);
}

char	*search_path(t_shell_data *shell, char **cmd_args)
{
	int		i;
	char	*path_alpha;
	char	*path_final;

	i = 0;
	path_final = NULL;
	while (shell->env_char[i] != NULL)
	{
		if (ft_strncmp(shell->env_char[i], "PATH=", 5) == 0)
		{
			path_alpha = ft_strchr(shell->env_char[i], '=') + 1;
			if (path_alpha != NULL)
			{
				shell->paths = ft_split(path_alpha, ':');
				path_final = search_final_path(shell, cmd_args);
				free_array(&shell->paths);
				shell->paths = NULL;
			}
			break ;
		}
		i++;
	}
	return (path_final);
}
