/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_count_len_words_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	allocation_len_and_start(int total_args, int **len_words, int **start,
		t_shell_data *shell)
{
	*len_words = (int *)malloc(sizeof(int) * total_args);
	if (*len_words == NULL)
		exit_1_malloc(&shell);
	*start = (int *)malloc(sizeof(int) * total_args);
	if (*start == NULL)
		exit_1_malloc(&shell);
}

void	initialize_values(t_parsing_values *values)
{
	values->i = 0;
	values->count = 0;
	values->in_args = 0;
	values->y = 0;
	values->len = 0;
	values->quote = 0;
}
