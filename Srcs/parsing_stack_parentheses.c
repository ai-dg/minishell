/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stack_parentheses.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/24 16:40:46 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	remove_parentheses_string(char *str, t_shell_data *shell)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_str == NULL)
	{
		ft_fprintf(stderr, "Memory allocation failed\n");
		exit_1_malloc(&shell);
	}
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')')
		{
			new_str[j++] = str[i];
		}
		i++;
	}
	new_str[j] = '\0';
	ft_strcpy(str, new_str);
	free_variable((void **)&new_str);
}

void	fill_p_execute_shell(t_cmd *cmd, char ***parsed, int *i, int *j)
{
	int	x;

	x = *i;
	cmd->p_execute = ft_strdup((*parsed)[x]);
	x++;
	if ((*parsed)[x])
	{
		while ((*parsed)[x] && x <= *j)
		{
			if (!ft_strchr((*parsed)[x], '|') && !ft_strchr((*parsed)[x], '>')
				&& !ft_strchr((*parsed)[x], '<'))
				cmd->p_execute = ft_fstrjoin(cmd->p_execute, " ", FIRST);
			cmd->p_execute = ft_fstrjoin(cmd->p_execute, (*parsed)[x], FIRST);
			x++;
		}
	}
}

void	remove_string_in_parentheses(char ***parsed, int *i, int *j)
{
	int	x;

	x = *i;
	while (x <= *j)
	{
		if ((*parsed)[x] != NULL)
		{
			free((*parsed)[x]);
			if (x == *i)
				(*parsed)[x] = ft_strdup("42");
			else
				(*parsed)[x] = ft_strdup("");
		}
		x++;
	}
}

void	remove_empty_strings(char ***parsed)
{
	int	read;
	int	write;

	read = 0;
	write = 0;
	while ((*parsed)[read])
	{
		if (ft_strcmp((*parsed)[read], "") != 0)
		{
			if (read != write)
			{
				(*parsed)[write] = (*parsed)[read];
				(*parsed)[read] = NULL;
			}
			write++;
		}
		else
		{
			free_variable((void **)&(*parsed)[read]);
			(*parsed)[read] = NULL;
		}
		read++;
	}
	while (write < read)
		(*parsed)[write++] = NULL;
}

void	parentheses_traitement(char **parsed, t_cmd *cmd, int *i,
		t_shell_data *shell)
{
	int	j;
	int	len;

	if (ft_strncmp(parsed[*i], "(", 1) == 0)
	{
		cmd->in_parentheses = true;
		j = *i;
		len = 0;
		while (parsed[j])
		{
			len += ft_strlen(parsed[j]);
			if (ft_strncmp(parsed[j], ")", 1) == 0
				|| parsed[j][ft_strlen(parsed[j]) - 1] == ')')
				break ;
			j++;
		}
		fill_p_execute_shell(cmd, &parsed, i, &j);
		remove_parentheses_string(cmd->p_execute, shell);
		remove_string_in_parentheses(&parsed, i, &j);
		remove_empty_strings(&parsed);
	}
}
