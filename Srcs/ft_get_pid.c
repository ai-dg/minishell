/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:46:57 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:34 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	end_of_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

int	extract_pid(char *buf)
{
	char	*trimmed;
	char	*numb;
	int		p_pid;

	p_pid = 0;
	trimmed = ft_strtrim(buf, " ");
	numb = ft_substr(trimmed, 0, end_of_digits(trimmed));
	p_pid = ft_atoi(numb);
	free_variable((void **)&trimmed);
	free_variable((void **)&numb);
	return (p_pid);
}

void	get_ps_children(t_shell_data *shell, int pip[2], char *ps[])
{
	close(pip[0]);
	if (dup2(pip[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit_1(&shell);
	}
	execve("/usr/bin/ps", ps, shell->env_char);
	perror("execve");
	close(pip[1]);
	exit_1(&shell);
}

void	find_pid_value(t_shell_data *shell, int pip[2], int *p_pid, char *buf)
{
	close(pip[1]);
	buf = get_next_line(pip[0]);
	while (buf)
	{
		if (ft_strstr(buf, &shell->av[0][2]))
		{
			*p_pid = extract_pid(buf);
			free_variable((void **)&buf);
			break ;
		}
		free_variable((void **)&buf);
		buf = get_next_line(pip[0]);
	}
	wait(0);
	close(pip[0]);
}

int	ft_get_pid(t_shell_data *shell)
{
	int			pid;
	int			p_pid;
	char		*buf;
	int			pip[2];
	static char	*ps[] = {"ps", NULL};

	buf = NULL;
	if (pipe(pip) < 0)
		return (fprintf(stderr, "pipe error"));
	p_pid = 0;
	pid = fork();
	if (pid == 0)
		get_ps_children(shell, pip, ps);
	else
		find_pid_value(shell, pip, &p_pid, buf);
	return (p_pid);
}
