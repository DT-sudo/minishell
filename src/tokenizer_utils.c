/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:41:29 by dt                #+#    #+#             */
/*   Updated: 2025/09/02 18:17:42 by dt               ###   ########.fr       */
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
			res[2] = TOKEN_RDR_OUT; // 5
			if (*(input + 1) == '>')
			{
				res[1] = ++i;
				res[2] = TOKEN_APPND; // 6
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
			res[2] = TOKEN_RDR_IN; // 4
			if (*(input + 1) == '<')
			{
				res[1] = ++i;
				res[2] = TOKEN_HERE; // 7
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
	res[2] = TOKEN_PIPE; // 3
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
	res[2] = TOKEN_NVP; // 8
	return (res);
}

