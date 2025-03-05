/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_here_doc_logic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static bool	if_expand_in_doc(char *inst, int *i)
{
	int	x;

	x = *i + 2;
	while (inst[x] == ' ' || inst[x] == '\t')
	{
		x++;
	}
	while (inst[x] && (inst[x] != '<' || !ft_is_whitespace(inst[x])))
	{
		if (inst[x] == '\'' || inst[x] == '"')
			return (true);
		x++;
	}
	return (false);
}

static int	get_expand_in_doc_size(char *inst)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (inst[i])
	{
		if (inst[i] == '<' && inst[i + 1] && inst[i + 1] == '<')
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}

int	*add_logic_expand_in_doc(char *inst, t_shell_data *shell)
{
	int	i;
	int	count;
	int	x;

	x = 0;
	count = get_expand_in_doc_size(inst);
	shell->to_expand_in_doc = (int *)malloc(sizeof(int) * count);
	if (shell->to_expand_in_doc == NULL)
		exit_1_malloc(&shell);
	i = 0;
	while (inst[i] && x < count)
	{
		if (inst[i] == '<' && inst[i + 1] && inst[i + 1] == '<')
		{
			shell->to_expand_in_doc[x++] = if_expand_in_doc(inst, &i);
			i += 2;
		}
		else
			i++;
	}
	return (shell->to_expand_in_doc);
}
