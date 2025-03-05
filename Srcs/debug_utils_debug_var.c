/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils_debug_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:21:51 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/14 20:40:38 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	debug_char(char *str, char *color, t_shell_data *shell)
{
	if (shell->debug_mode == DEV)
		printf("%s --- %s --- %s\n", color, str, RESET);
}

void	debug_nbr(char *label, long long int i, char *color,
		t_shell_data *shell)
{
	if (shell->debug_mode == DEV)
		printf("%s --- %s : %lld --- %s\n", color, label, i, RESET);
}

void	set_color(char *color)
{
	printf("%s", color);
}

void	mark(char *txt, t_shell_data *shell)
{
	if (shell->debug_mode == DEV)
	{
		if (txt)
			printf("%s --- %s --- %s\n", RED, txt, RESET);
		else
			printf("%s --- DEBUG MARK --- %d%s\n", RED, ++shell->debug_count,
				RESET);
	}
}

void	debug_chars(char **chars_array, char *debug_msg)
{
	printf("\n\n-------------------%s : \n",
		debug_msg);
	print_splitted(chars_array);
	printf("-------------------%s : \n\n",
		debug_msg);
}
