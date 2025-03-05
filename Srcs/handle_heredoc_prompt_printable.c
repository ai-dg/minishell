/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_prompt_printable.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:04:18 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	init_special(t_special_bar *special)
{
	special->tmp = NULL;
	special->j = 0;
	special->single_quote = '\'';
	special->close_it = true;
	special->position_of_str = 0;
	special->prompt_len = 0;
	special->i = 0;
	special->k = 0;
}

static void	add_special_non_printable(t_special_bar *special, char *prompt)
{
	while (special->i < special->prompt_len)
	{
		special->tmp[special->j++] = prompt[special->i];
		if (prompt[special->i] == '\\' && prompt[special->i + 1] == ' '
			&& is_printable_but_no_bar(prompt[special->i - 1]) == true)
		{
			special->position_of_str = special->i - 1;
			while (prompt[special->i + 2] > 32 && prompt[special->i + 2] < 127)
			{
				special->tmp[special->j++] = prompt[++special->i];
			}
			special->tmp[special->j++] = prompt[++special->i];
			special->tmp[special->j++] = special->single_quote;
			special->close_it = true;
		}
		special->i++;
	}
}

void	special_bar_non_printable_add(char **prompt, t_shell_data *shell)
{
	t_special_bar	special;

	init_special(&special);
	special.prompt_len = ft_strlen(*prompt);
	special.tmp = (char *)malloc(sizeof(char) * (special.prompt_len * 2 + 100));
	ft_reset_buffer(special.tmp, special.prompt_len * 2 + 1);
	if (special.tmp == NULL)
		exit_1_malloc(&shell);
	add_special_non_printable(&special, *prompt);
	if (special.close_it == true && special.position_of_str > 0
		&& special.position_of_str < special.j)
	{
		special.k = special.j;
		while (special.k >= 1 && special.k > special.position_of_str)
		{
			special.tmp[special.k] = special.tmp[special.k - 1];
			special.k--;
		}
		special.tmp[special.position_of_str] = special.single_quote;
		special.j++;
	}
	special.tmp[special.j] = '\0';
	free_variable((void **) prompt);
	*prompt = ft_strdup(special.tmp);
	free_variable((void **)&special.tmp);
}
