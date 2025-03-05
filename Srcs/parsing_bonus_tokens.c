/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:24:09 by ls                #+#    #+#             */
/*   Updated: 2024/06/18 13:36:05 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*move_pointer(char *ptr, int moves)
{
	while (moves--)
		ptr++;
	return (ptr);
}

static void	first_condition(int *toki, t_smart_token *token)
{
	if (token->index_and == -1 && token->index_or == -1)
	{
		*toki = 2;
		token->index = -1;
	}
	else if ((token->index_or == -1 && token->index_and) || (token->index_and
			> -1 && token->index_or > -1 && token->index_and < token->index_or))
	{
		*toki = 0;
		token->index = token->index_and;
	}
	else if ((token->index_and == -1 && token->index_or) || (token->index_and
			> -1 && token->index_or > -1 && token->index_or < token->index_and))
	{
		*toki = 1;
		token->index = token->index_or;
	}
}

static void	second_condition(t_smart_token *token)
{
	if (token->index < 0)
	{
		token->extract = ft_strdup(token->remain_str);
		token->remain_str = NULL;
	}
	else
	{
		token->extract = ft_substr(token->remain_str, 0, token->index);
		token->remain_str = move_pointer(token->remain_str, token->index + 2);
	}
}

static void	init_token(t_smart_token *token)
{
	token->index_and = 0;
	token->index_or = 0;
	token->index = 0;
	token->extract = NULL;
	token->remain_str = NULL;
}

char	*ft_smart_tokeniser(char *str, int *toki)
{
	t_smart_token	token;
	static char		*tokens[] = {"&&", "||", "--"};

	init_token(&token);
	if (token.remain_str == NULL && str)
		token.remain_str = str;
	if (token.remain_str == NULL && !str)
		return (NULL);
	token.index_and = ft_strstr_index(token.remain_str, tokens[0]);
	token.index_or = ft_strstr_index(token.remain_str, tokens[1]);
	first_condition(toki, &token);
	second_condition(&token);
	return (token.extract);
}
