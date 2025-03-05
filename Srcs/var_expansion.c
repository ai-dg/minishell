/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 06:52:45 by ls                #+#    #+#             */
/*   Updated: 2024/06/27 14:18:16 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_status_from_sig(t_shell_data *shell)
{
	shell->exit_status = g_receipt + 128;
	shell->g_receipt = 0;
	g_receipt = 0;
	return (shell->exit_status);
}

char	*expand_exit_status(t_shell_data *shell)
{
	if (shell->exit_status != 0 && g_receipt == 0)
		return (ft_itoa(shell->exit_status));
	if (g_receipt != 0 && shell->exit_status == 0)
		return (ft_itoa(get_status_from_sig(shell)));
	return (ft_itoa(shell->exit_status));
}

char	*find_value(char *to_expand, t_shell_data *shell, int trim_space)
{
	if (ft_strlen(to_expand) == 1 && to_expand[0] == '$')
		return (ft_strdup("$"));
	if (ft_strlen(to_expand) == 2 && has_to_ignore(to_expand[1]))
		return (ft_strdup(to_expand));
	if (ft_strlen(to_expand) >= 2 && to_expand[0] == '$'
		&& ft_isdigit(to_expand[1]))
		return (ft_strdup(""));
	if (ft_strncmp(to_expand, "$UID", ft_strlen(to_expand)) == 0)
		return (ft_getuid());
	if (strncmp(to_expand, "$$", 2) == 0)
		return (ft_itoa((int)ft_get_pid(shell)));
	if (strncmp(to_expand, "$?", 2) == 0)
		return (expand_exit_status(shell));
	if (is_duplicate_key(shell->env, &to_expand[1]))
		return (shell->echo_in_variable = true,
			ft_strdup(get_value_from_key(shell->env, &to_expand[1])));
	if (is_duplicate_key(shell->session, &to_expand[1]))
		return (shell->echo_in_variable = true,
			ft_strdup(get_value_from_key(shell->session, &to_expand[1])));
	if (trim_space == 1)
		return (ft_strdup(""));
	return (ft_strdup(""));
}

bool	do_nothing_in_vars(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strtrim(str, " \t");
	while (tmp[i])
	{
		if (i % 2 == 0 && tmp[i] != '$')
			return (false);
		if (i % 2 != 0 && has_to_ignore(tmp[i]))
			return (false);
		i++;
	}
	free_variable((void **)&tmp);
	return (true);
}

char	*expand_variable(char *str, t_shell_data *shell)
{
	char	*tmp;

	tmp = NULL;
	if (str && str[0] == '$' && str[1] == '\0')
		return (ft_strdup("$"));
	if (find_index('$', str) == -1)
	{
		return (str);
	}
	else if (ft_strncmp(str, "$HOME*", ft_strlen(str)) == 0)
	{
		tmp = get_value_from_key(shell->env, "HOME");
		if (tmp)
		{
			if (str == NULL && str[0] == '\0')
				free_variable((void **)&str);
			return (ft_strdup(tmp));
		}
		return (NULL);
	}
	else
	{
		str = replace_in_str(str, shell);
	}
	return (str);
}
