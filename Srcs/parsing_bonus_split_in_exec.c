/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_split_in_exec.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/22 18:51:01 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	create_and_link_exec_unit(char ***temp, int index,
		t_exec_unit **exec_unit, t_exec_unit *parent)
{
	t_exec_unit	*new_exec_unit;

	new_exec_unit = create_exec_unit((*temp)[index], IS_A_BRANCH, parent);
	if (new_exec_unit != NULL && new_exec_unit != *exec_unit)
	{
		if (*exec_unit != NULL)
			free_exec_unit(*&exec_unit);
		*exec_unit = new_exec_unit;
	}
}

static void	attach_sub_units(char ***temp, int index, t_exec_unit **exec_unit)
{
	t_exec_unit	*new_exec_unit;

	new_exec_unit = create_subs(*exec_unit, (*temp)[index - 2], (*temp)[index
			- 1]);
	if (new_exec_unit != NULL && new_exec_unit != *exec_unit)
	{
		if (*exec_unit != NULL)
			free_exec_unit(*&exec_unit);
		*exec_unit = new_exec_unit;
	}
}

static void	fill_exec_unit(int *args, char ***temp, t_exec_unit **exec_unit)
{
	while (*args >= 0)
	{
		if (ft_strlen((*temp)[*args]) > 2)
		{
			(*args)--;
			continue ;
		}
		else
		{
			if (!*exec_unit)
			{
				create_and_link_exec_unit(temp, *args, exec_unit, NULL);
			}
			else
			{
				create_and_link_exec_unit(temp, *args, exec_unit, *exec_unit);
			}
			attach_sub_units(temp, *args, exec_unit);
			(*args) -= 3;
		}
	}
}

static void	if_top_is_zero(char **prompt, t_exec_unit **exec_unit)
{
	t_exec_unit	*new_exec_unit;

	new_exec_unit = create_exec_unit(*prompt, IS_A_LEAF, NULL);
	if (new_exec_unit != NULL && new_exec_unit != *exec_unit)
	{
		if (*exec_unit != NULL)
		{
			free_exec_unit(*&exec_unit);
		}
		*exec_unit = new_exec_unit;
	}
}

t_exec_unit	*split_in_exec_units(char *prompt, t_exec_unit *exec_unit)
{
	char	**temp;
	int		args;
	int		top;

	temp = NULL;
	top = get_root_split_index_rev(prompt);
	if (top == 0)
	{
		if_top_is_zero(&prompt, &exec_unit);
		return (exec_unit);
	}
	temp = ft_split_at_index(prompt, top);
	args = count_args(temp) - 1;
	fill_exec_unit(&args, &temp, &exec_unit);
	return (free_array(&temp), exec_unit);
}
