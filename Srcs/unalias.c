/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:55:09 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 12:38:24 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	unalias_m(t_shell_data *shell, char **inst)
{
	if (is_duplicate_key(shell->alias, inst[1]))
		extract_node_with_key(&shell->alias, inst[1], DELETE);
	return (0);
}
