/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_create_subs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/18 13:08:15 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	handle_left_prompt(t_exec_unit **left, t_exec_unit **parent,
		char *left_prompt)
{
	if (!ft_strstr(left_prompt, "||") && !ft_strstr(left_prompt, "&&"))
		*left = create_exec_unit(left_prompt, IS_A_LEAF, *parent);
	if (ft_strstr(left_prompt, "||") || ft_strstr(left_prompt, "&&"))
	{
		*left = split_in_exec_units(left_prompt, *left);
	}
}

static void	handle_right_prompt(t_exec_unit **right, t_exec_unit **parent,
		char *right_prompt)
{
	if (!ft_strstr(right_prompt, "||") && !ft_strstr(right_prompt, "&&"))
		*right = create_exec_unit(right_prompt, IS_A_LEAF, *parent);
	if (ft_strstr(right_prompt, "||") || ft_strstr(right_prompt, "&&"))
	{
		*right = split_in_exec_units(right_prompt, *right);
	}
}

t_exec_unit	*create_subs(t_exec_unit *parent, char *left_prompt,
		char *right_prompt)
{
	t_exec_unit	*left;
	t_exec_unit	*right;

	left = NULL;
	right = NULL;
	if (!left_prompt)
		left = NULL;
	if (!right_prompt)
		right = NULL;
	if (!left_prompt || !right_prompt)
	{
		join_exec_unit(NULL, NULL, &parent);
		return (NULL);
	}
	if (left_prompt)
		handle_left_prompt(&left, &parent, left_prompt);
	if (right_prompt)
		handle_right_prompt(&right, &parent, right_prompt);
	if (left)
		left->p_unit = parent;
	if (right)
		right->p_unit = parent;
	join_exec_unit(left, right, &parent);
	return (parent);
}
