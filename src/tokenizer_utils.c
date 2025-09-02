/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:41:29 by dt                #+#    #+#             */
/*   Updated: 2025/08/29 17:58:17 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*tk_out_appnd(char *input, int res[3])
{
	int	i;

	i = 0;
	while (*input != '\0' && *input != ' ' && *input != '	')
	{
		if (*input == '>')
		{
			res[0] = i;
			res[1] = ++i;
			res[2] = 6;
			if (*(input + 1) == '>')
			{
				res[1] = ++i;
				res[2] = 7;
				break ;
			}
		}
		input++;
		i++;
	}
	return (res);
}

int	*tk_in_here(char *input, int res[3])
{
	int	i;

	i = 0;
	while (*input != '\0' && *input != ' ' && *input != '	')
	{
		if (*input == '<')
		{
			res[0] = i;
			res[1] = ++i;
			res[2] = 5;
			if (*(input + 1) == '<')
			{
				res[1] = ++i;
				res[2] = 8;
				break ;
			}
		}
		input++;
		i++;
	}
	return (res);
}

int	*tk_pipe(char *input, int res[3])
{
	int	i;

	i = 0;
	while (*input != '\0' && *input != ' ' && *input != '	')
	{
		if (*input == '|')
		{
			res[0] = i;
			res[1] = i + 1;
			break ;
		}
		else
			input++;
		i++;
	}
	res[2] = 4;
	return (res);
}

int	*tk_envp_v(char *input, int res[3])
{
	int	i;
	int	inword;

	i = 0;
	inword = 0;
	while (*input != '\0' && *input != ' ' && *input != '	')
	{
		if (*input == '$' && !inword)
		{
			res[0] = i++;
			input++;
			inword = 1;
		}
		else if (*input == '$' && inword)
			break;
		else if (inword)
		{
			input++;
			i++;
		}
	}
	res[1] = i;
	res[2] = 9;
	return (res);
}

