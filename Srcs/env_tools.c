/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:57:26 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/20 19:10:15 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	print_env_list(char *pre, t_env *lst, char **inst, bool ingore_void)
{
	t_env	*tmp;

	(void)inst;
	tmp = lst;
	if (!lst)
		return (1);
	while (lst)
	{
		if (pre)
			printf("%s ", pre);
		if (lst->value)
			printf("%s=%s\n", lst->key, lst->value);
		if (!lst->value && !ingore_void)
			printf("%s\n", lst->key);
		lst = lst->next;
	}
	lst = tmp;
	return (0);
}

int	print_var(t_env *lst, char *key)
{
	char	*value;
	int		res;

	res = 1;
	value = get_value_from_key(lst, key);
	if (value)
	{
		res = 0;
		printf("%s\n", value);
	}
	return (res);
}

int	printenv_m(t_shell_data *shell, char **inst)
{
	int	res;

	res = 1;
	if (inst[1])
	{
		if (is_duplicate_key(shell->env, inst[1]))
			res = print_var(shell->env, inst[1]);
		else if (is_duplicate_key(shell->session, inst[1]))
			res = print_var(shell->session, inst[1]);
	}
	return (shell->exit_status = res, res);
}

void	remove_env_arg(char **inst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (inst[i])
	{
		if (ft_strcmp(inst[i], "env") == 0)
		{
			free_variable((void **)&inst[i]);
			i++;
			continue ;
		}
		inst[j] = inst[i];
		i++;
		j++;
	}
	inst[j] = NULL;
}

t_env	*set_minimal_env(t_shell_data *shell)
{
	char	*cwd;
	char	*lstcmd;
	t_env	*env;
	char	*shlvl;

	cwd = getcwd(NULL, 0);
	shlvl = ft_itoa(shell->shell_level);
	env = new_env_node("PWD", cwd, shell);
	push_back_env_node(&env, new_env_node("SHLVL", shlvl, shell));
	lstcmd = ft_strdup("/usr/bin/env");
	push_back_env_node(&env, new_env_node("_", lstcmd, shell));
	return (free_variable((void **)&lstcmd), env);
}
