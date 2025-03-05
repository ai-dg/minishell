/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_buildin_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 13:18:55 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	is_builtin(char *func)
{
	int					i;
	static const char	*funcs[] = {"exit", "clear", "pwd", "echo", "cd",
		"export", "unset", "env", "alias", "unalias", NULL};

	i = 0;
	while (funcs[i])
	{
		if (ft_strncmp(func, funcs[i], ft_strlen(func)) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	get_index(char *inst)
{
	int					i;
	static const char	*keys[] = {"exit", "clear", "pwd", "echo", "cd",
		"export", "unset", "env", "set", "printenv", "alias", "unalias",
		NULL};

	i = 0;
	if (ft_found_char(inst, '='))
		return (10);
	while (keys[i])
	{
		if (ft_strncmp(keys[i], inst, ft_strlen(keys[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exe_builtin_cmd(char *inst, char **argv, t_shell_data *shell)
{
	int			index;
	static int	(*exe[])(t_shell_data *, char **) = {exit_m, clear_m,
		pwd_m, echo_m, cd_m, export_m, unset_m, env_m, set_m, printenv_m,
		alias_m, unalias_m};

	index = get_index(inst);
	if (index >= 0)
	{
		exe[index](shell, argv);
		return (0);
	}
	printf("finishing exe_builtin_cmd\n");
	return (shell->exit_status = 1, -1);
}

int	reopen_stdin_if_needed(void)
{
	struct stat	st;
	int			fd;
	int			status;

	status = fstat(STDIN_FILENO, &st);
	if (status == -1)
	{
		if (errno == EBADF)
		{
			fd = open("/dev/tty", O_RDONLY);
			if (fd == -1)
				return (perror("open /dev/tty"), -1);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("dup2"), close(fd), -1);
		}
		else
			return (perror("fstat"), -1);
	}
	return (0);
}
