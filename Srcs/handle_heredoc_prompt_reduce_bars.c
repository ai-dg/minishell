/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt_reduce_bars.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:18 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	init_reduce(t_reduce_half_of_bars *reduce, char *prompt,
		t_shell_data *shell)
{
	reduce->i = 0;
	reduce->j = 0;
	reduce->k = 0;
	reduce->len = ft_strlen(prompt);
	reduce->odd = false;
	reduce->tmp = (char *)malloc(sizeof(char) * (reduce->len + 1));
	if (reduce->tmp == NULL)
		exit_1_malloc(&shell);
	reduce->count = 0;
	reduce->to_copy = 0;
}

static void	if_found_bars(t_reduce_half_of_bars *reduce, char *prompt)
{
	reduce->count = 0;
	while (prompt[reduce->i + reduce->count] == '\\')
		reduce->count++;
	if (reduce->count % 2 == 0)
		reduce->to_copy = reduce->count / 2;
	else
	{
		reduce->to_copy = (reduce->count - 1) / 2;
		reduce->odd = true;
	}
	reduce->k = 0;
	while (reduce->k < reduce->to_copy)
	{
		reduce->tmp[reduce->j++] = '\\';
		reduce->k++;
	}
	if (reduce->odd == true)
		reduce->tmp[reduce->j++] = 127;
	reduce->i += reduce->count - 1;
}

void	reduce_half_of_bars(char *prompt, t_shell_data *shell)
{
	t_reduce_half_of_bars	reduce;

	init_reduce(&reduce, prompt, shell);
	while (prompt[reduce.i] != '\0')
	{
		if (prompt[reduce.i] == '\\')
			if_found_bars(&reduce, prompt);
		else
			reduce.tmp[reduce.j++] = prompt[reduce.i];
		reduce.odd = false;
		reduce.i++;
	}
	reduce.tmp[reduce.j] = '\0';
	ft_strcpy(prompt, reduce.tmp);
	free(reduce.tmp);
}
