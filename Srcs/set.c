/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:19:10 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/13 12:11:08 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	set_m(t_shell_data *shell, char **inst)
{
	(void)inst;
	return (print_env_list(NULL, shell->session, inst, true));
}
