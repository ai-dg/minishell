/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unit_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:56:46 by ls                #+#    #+#             */
/*   Updated: 2024/06/18 10:46:11 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_exec_unit_prefix(t_exec_unit *exec_unit)
{
	if (!exec_unit)
		return ;
	if (exec_unit->p_unit && exec_unit->p_unit->prompt)
		printf("(%s)->-%s-\n", exec_unit->p_unit->prompt, exec_unit->prompt);
	else
		printf("-%s-\n", exec_unit->prompt);
	if (exec_unit->l_unit)
		print_exec_unit_prefix(exec_unit->l_unit);
	if (exec_unit->r_unit)
		print_exec_unit_prefix(exec_unit->r_unit);
}

void	print_exec_unit_postfix(t_exec_unit *exec_unit)
{
	if (!exec_unit)
		return ;
	if (exec_unit->p_unit)
		printf("(%s)->(%s)\n", exec_unit->p_unit->prompt, exec_unit->prompt);
	else
		printf("(%s)\n", exec_unit->prompt);
	if (exec_unit->r_unit)
		print_exec_unit_prefix(exec_unit->r_unit);
	if (exec_unit->l_unit)
		print_exec_unit_prefix(exec_unit->l_unit);
}
