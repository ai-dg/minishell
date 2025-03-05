/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_expander.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:48:06 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/29 10:16:09 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static char	*move_cpy(char **cpy, int len)
{
	while (**cpy != '\0' && len--)
		(*cpy)++;
	return (*cpy);
}

static void	init_var_expander(t_var_ex *v, char *str)
{
	v->final = NULL;
	v->to_expand = NULL;
	v->replaced = NULL;
	v->cpy = str;
	v->occurences = ft_count_occurences('$', str);
	v->length = 0;
	v->index = 0;
	v->next = 1;
	v->trim_space = 0;
}

static void	setup_expander(t_var_ex *v)
{
	v->index = find_dollar_index('$', v->cpy);
	if (v->index > 0)
		v->final = ft_fstrjoin(v->final, ft_substr(v->cpy, 0, v->index), BOTH);
	v->cpy = move_cpy(&v->cpy, v->index);
	v->index = find_dollar_index('$', v->cpy);
	v->length = var_length(v->cpy, v->index);
	v->to_expand = ft_substr(v->cpy, v->index, v->length);
}

static void	var_replacer(t_var_ex *v, t_shell_data *shell)
{
	v->replaced = find_value(v->to_expand, shell, v->trim_space);
	if (has_quotes(v->replaced))
		encode_quotes(v->replaced);
	if (v->replaced)
		v->final = ft_fstrjoin(v->final, v->replaced, BOTH);
}

char	*replace_in_str(char *str, t_shell_data *shell)
{
	t_var_ex	v;

	init_var_expander(&v, str);
	if (!str)
		return (NULL);
	shell->dollar_expansion = true;
	shell->dollar_expansion_trim = true;
	while (v.occurences--)
	{
		setup_expander(&v);
		if (has_to_expand(str, v.to_expand, v.next)
			|| shell->in_here_doc == true)
			var_replacer(&v, shell);
		else
			v.final = ft_fstrjoin(v.final, v.to_expand, FIRST);
		free_variable((void **)&v.to_expand);
		v.cpy = move_cpy(&v.cpy, v.length);
		v.index = find_dollar_index('$', v.cpy);
		v.next++;
	}
	v.final = ft_fstrjoin(v.final, v.cpy, FIRST);
	free_variable((void **)&v.to_expand);
	return (v.final);
}
