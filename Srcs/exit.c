/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:00:01 by ls                #+#    #+#             */
/*   Updated: 2024/06/30 16:32:36 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	check_long_long(int is_negative, int digit, long long int result)
{
	if (is_negative)
	{
		if (result < (LLONG_MIN + digit) / 10)
			return (true);
	}
	else
	{
		if (result > (LLONG_MAX - digit) / 10)
			return (true);
	}
	return (false);
}

static bool	check_str(const char *str, bool is_negative, long long int result,
		int digit)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (false);
		digit = *str - '0';
		if (check_long_long(is_negative, digit, result))
			return (false);
		if (is_negative)
			result = result * 10 - digit;
		else
			result = result * 10 + digit;
		str++;
	}
	return (true);
}

bool	is_valid_long_long(const char *str)
{
	bool			is_negative;
	long long int	result;
	int				digit;
	bool			check;

	check = true;
	digit = 0;
	result = 0;
	is_negative = false;
	if (!str || str[0] == '\0')
		return (false);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_negative = true;
		str++;
	}
	if (str[0] == '\0')
		return (false);
	check = check_str(str, is_negative, result, digit);
	if (check == false)
		return (false);
	return (true);
}

static void	resize_and_atoll(int *exit_status, char ***argv)
{
	*exit_status = ft_atoll((*argv)[1]);
	if (*exit_status > 256 || *exit_status < 0)
		*exit_status = resize_exit_status(*exit_status);
}

int	exit_m(t_shell_data *shell, char **argv)
{
	int	args;
	int	exit_status;

	args = ft_count_args(argv);
	if (args == 1)
		exit_status = 0;
	if (argv[1] != NULL && !is_valid_long_long(argv[1]))
	{
		exit_msg(argv[1], "numeric argument required\n");
		exit_status = 2;
	}
	else if (args > 2)
	{
		ft_fprintf(stderr, "minishell: %s: too many arguments\n", argv[0]);
		return (exit_status = 1, shell->exit_status = exit_status, exit_status);
	}
	else if (argv != NULL && only_numbers(argv[1]) == true && args == 2)
	{
		resize_and_atoll(&exit_status, &argv);
	}
	if (shell->exit_signals != 0)
		exit_status = shell->exit_signals;
	clear_memory(shell);
	printf("exit\n");
	exit(exit_status);
}
