/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:39:29 by dt                #+#    #+#             */
/*   Updated: 2025/08/29 08:43:38 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calc_len(t_input *new_word)
{
	int	len;

	len = 0;
	while (new_word->word[len] != '\0')
		len++;
	return (len);
}

int	*tk_word(char *input, int res[3])
{
	int	inword;
	int	i;

	i = 0;
	inword = 0;
	while (*input != '\0' && *input != ' ' && *input != '	' && *input != '<'
			&& *input != '>' && *input != '|')
	{
		if (!inword)
		{
			inword = 1;
			res[0] = i;
		}
		i++;
		input++;
	}
	res[1] = i;
	res[2] = 1;
	return (res);
}

// 39 == '
int	*tk_s_quotes(char *input, int res[3])
{
	int	i;
	int	inword;

	i = 0;
	inword = 0;
	while (*input != '\0')
	{
		if (*input == '\'' && !inword)
		{
			inword = 1;
			res[0] = i + 1;
			res[2] = 2;
		}
		else if (*input == '\'' && inword)
		{
			res[1] = i;
			break ;
		}
		input++;
		i++;
	}
	return (res);
}

// 34 == "
int	*tk_d_quotes(char *input, int res[3])
{
	int	i;
	int	inword;

	i = 0;
	inword = 0;
	while (*input != '\0')
	{
		if (*input == '"' && !inword)
		{
			inword = 1;
			res[0] = i + 1;
			res[2] = 3;
		}
		else if (*input == '"' && inword)
		{
			res[1] = i;
			break ;
		}
		input++;
		i++;
	}
	return (res);
}
