/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_and_system.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:24:52 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/27 17:02:02 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static bool	multiple_and_case_error(char *inst, int *i, int mode)
{
	int	x;
	int	count;

	count = 0;
	x = (*i) - 1;
	while (x >= 0 && inst[x] == '&')
	{
		count++;
		x--;
	}
	if ((count == 3 || (ft_strlen(inst) == 1 && count == 1)) && mode == VERBOSE)
	{
		ft_fprintf(stderr,
			"minishell: syntax error near unexpected token `&'\n");
		return (true);
	}
	else if ((count >= 3 || (ft_strlen(inst) == 2 && count == 2))
		&& mode == VERBOSE)
	{
		ft_fprintf(stderr,
			"minishell: syntax error near unexpected token `&&'\n");
		return (true);
	}
	return (false);
}

static bool	find_errors(char *inst, int *i, int mode)
{
	int	x;
	int	count;

	count = 0;
	if (multiple_and_case_error(inst, i, mode) == true)
		return (true);
	x = (*i) - 1;
	while (x >= 0 && inst[x] == '&')
		x--;
	x--;
	while (x >= 0 && is_special_char(inst[x]) == false)
	{
		if (x >= 0 && inst[x] > 32 && inst[x] < 127
			&& is_special_char(inst[x]) == false)
			return (false);
		x--;
	}
	print_invalid_args_and_message(count, mode);
	return (true);
}

static bool	is_printable_after(char *inst, int i)
{
	while (i < (int)ft_strlen(inst) - 1 && inst[i])
	{
		if (inst[i] && is_printable_but_no_special(inst[i],
				SKIP_PARENTHESIS) == true)
			return (true);
		i++;
	}
	return (false);
}

bool	readline_needed(char *inst)
{
	int	i;

	i = 1;
	while (inst[i])
	{
		if (inst[i] == '&' && inst[i - 1] == '&')
		{
			if (is_printable_after(inst, i + 2) == false)
			{
				return (true);
			}
		}
		i++;
	}
	return (false);
}

bool	check_and_system(char **inst, t_shell_data *shell, int mode)
{
	int	i;

	i = 0;
	(void)shell;
	while ((*inst)[i])
	{
		if ((*inst)[i] == '&')
		{
			while ((*inst)[i] == '&' && (*inst)[i] != '\0')
				i++;
			if (find_errors(*inst, &i, mode) == true)
				return (true);
		}
		i++;
	}
	return (false);
}
