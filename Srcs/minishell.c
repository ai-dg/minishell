/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 11:35:31 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	ignore_signals(void)
{
	struct sigaction	monitoring;

	monitoring.sa_handler = SIG_IGN;
	sigemptyset(&monitoring.sa_mask);
	monitoring.sa_flags = 0;
	sigaction(SIGINT, &monitoring, NULL);
	sigaction(SIGQUIT, &monitoring, NULL);
	sigaction(SIGTERM, &monitoring, NULL);
}

void	monitor_parent(void)
{
	int	initial_ppid;

	ignore_signals();
	initial_ppid = ft_get_ppid();
	while (1)
	{
		if (ft_get_ppid() != initial_ppid)
		{
			reduce_number_shell_level();
			exit(EXIT_SUCCESS);
		}
	}
}

int	recover_number_shell_level(void)
{
	int		fd;
	int		number;
	char	buffer[16];
	ssize_t	bytes_read;

	number = 0;
	fd = open(".shell_level", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		number = atoi(buffer);
	}
	close(fd);
	return (number);
}

int	init_and_start_shell(t_shell_data *shell, int ac, char **av, char **env)
{
	int	status;

	shell = init_shell();
	shell->av = av;
	shell->ac = ac;
	shell->sys_env = env;
	shell->debug_count = 0;
	shell->debug_mode = PROD;
	add_number_shell_level();
	if (recover_number_shell_level() == 0)
		shell->shell_level = 1;
	else
		shell->shell_level = recover_number_shell_level();
	check_start_mode(shell);
	sandbox(shell);
	load_historic(shell);
	set_env(shell);
	set_session(shell);
	init_signals(shell);
	script_exe(shell);
	init_rc_file(shell);
	welcome_message();
	shell_prompt(shell);
	status = shell->exit_status;
	return (free_malloc_exit_system(&shell), status);
}

int	main(int ac, char **av, char **env)
{
	pid_t			pid;
	t_shell_data	*shell;
	int				exit_status;

	exit_status = 0;
	shell = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		monitor_parent();
	else
	{
		exit_status = init_and_start_shell(shell, ac, av, env);
		return (exit_status);
	}
}
