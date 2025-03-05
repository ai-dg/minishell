/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:42:29 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/17 08:33:18 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	encode_quotes(char *replace)
{
	char	replace_dble;
	char	replace_sple;
	int		i;

	replace_dble = (char)130;
	replace_sple = (char)132;
	i = 0;
	while (replace[i])
	{
		if (replace[i] == '\'')
			replace[i] = replace_sple;
		if (replace[i] == '"')
			replace[i] = replace_dble;
		i++;
	}
}

void	decode_quotes_before_smart(char *replace)
{
	unsigned char	space_rple;
	unsigned char	sple_quote;
	unsigned char	dollar;
	int				i;

	space_rple = 0xDA;
	sple_quote = 0xDB;
	dollar = 0xDC;
	i = 0;
	while (replace[i])
	{
		if (replace[i] == space_rple)
			replace[i] = ' ';
		else if (replace[i] == sple_quote)
			replace[i] = '\'';
		else if (replace[i] == dollar)
			replace[i] = '$';
		i++;
	}
}

static void	init_smart_decode(t_smart_decode *dec)
{
	dec->replace_dble = (char)130;
	dec->replace_sple = (char)132;
	dec->space_rple = 0xDA;
	dec->sple_quote = 0xDC;
	dec->dollar = 0xDB;
}

void	decode_quotes_after_smart_quotes(char *replace)
{
	int				i;
	t_smart_decode	dec;

	init_smart_decode(&dec);
	i = 0;
	while (replace[i])
	{
		if (replace[i] == dec.replace_sple || replace[i] == dec.sple_quote)
			replace[i] = '\'';
		else if (replace[i] == dec.replace_dble)
			replace[i] = '"';
		else if (replace[i] == dec.space_rple)
			replace[i] = ' ';
		else if (replace[i] == dec.dollar)
			replace[i] = '$';
		i++;
	}
}

bool	has_to_expand(char *str, char *to_expand, int pos)
{
	int	index;

	(void)to_expand;
	index = 0;
	while (pos)
	{
		if (str[index])
		{
			if (index == 0)
				index += find_index('$', &str[index]);
			else
			{
				if (str[index + 1] && str[index + 1] == '$')
					index += find_index('$', &str[index + 2]) + 2;
				else
					index += find_index('$', &str[index + 1]) + 1;
			}
		}
		pos--;
	}
	if (swap_foreward(str, index))
	{
		return (true);
	}
	return (false);
}
