/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:26:11 by calbor-p          #+#    #+#             */
/*   Updated: 2024/07/01 11:45:25 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	debug_prompt(t_prompt prompt)
{
	if (prompt.cwd)
		printf("prompt.cwd  : %s\n", prompt.cwd);
	printf("prompt.host : %s\n", prompt.host);
	if (prompt.log)
		printf("prompt.log  : %s\n", prompt.log);
	if (prompt.path)
		printf("prompt.path : %s\n", prompt.path);
	printf("prompt.hst  :\n");
	print_splitted(prompt.hst);
}

char	*get_prompt(t_prompt prompt, char *line, t_shell_data *shell)
{
	line = ft_strjoin(BOLD_VIOLET, prompt.log);
	line = ft_strjoin_and_free(line, "@", shell);
	line = ft_strjoin_and_free(line, prompt.hst[0], shell);
	line = ft_strjoin_and_free(line, RESET, shell);
	line = ft_strjoin_and_free(line, ":", shell);
	line = ft_strjoin_and_free(line, BOLD_BLUE, shell);
	if (prompt.filter)
	{
		line = ft_fstrjoin(line, "~", FIRST);
		line = ft_fstrjoin(line, prompt.path, FIRST);
	}
	else
	{
		if (ft_strncmp(prompt.pwd, "//", 2) == 0)
			line = ft_fstrjoin(line, "/", FIRST);
		line = ft_strjoin_and_free(line, prompt.path, shell);
	}
	line = check_git(line);
	line = ft_fstrjoin(line, ft_strdup(RESET), BOTH);
	if (prompt.cwd && ft_strncmp("/root", prompt.cwd,
			ft_strlen(prompt.cwd)) == 0)
		line = ft_fstrjoin(line, "# ", FIRST);
	else
		line = ft_fstrjoin(line, "$ ", FIRST);
	return (line);
}

static void	prompt_pwd_filter(t_shell_data *shell, t_prompt *prompt)
{
	if (is_duplicate_key(shell->env, "HOME"))
	{
		prompt->cwd = get_value_from_key(shell->env, "HOME");
		if (ft_strlen(prompt->cwd) == 0 || !path_exist(prompt->cwd, NULL))
			prompt->cwd = NULL;
	}
	else
		prompt->cwd = NULL;
	if (prompt->cwd && ft_strncmp(prompt->cwd, prompt->path,
			ft_strlen(prompt->cwd)) == 0)
	{
		prompt->path = pass_str(prompt->cwd, prompt->path);
		prompt->filter = true;
	}
}

char	*prompt_line(t_shell_data *shell)
{
	t_prompt	prompt;
	char		*line;

	line = NULL;
	prompt.filter = false;
	prompt.pwd = get_value_from_key(shell->env, "PWD");
	ft_gethostname(prompt.host, 255);
	prompt.hst = ft_split(prompt.host, '.');
	if (!prompt.hst)
		return (NULL);
	prompt.path = NULL;
	prompt.path = getcwd(NULL, 0);
	if (!prompt.path)
		prompt.path = ft_strdup(get_value_from_key(shell->env, "PWD"));
	prompt_pwd_filter(shell, &prompt);
	prompt.log = getenv("LOGNAME");
	if (!prompt.log)
		prompt.log = get_login();
	line = get_prompt(prompt, line, shell);
	free_variable((void **)&prompt.path);
	return (free_array(&prompt.hst), line);
}
