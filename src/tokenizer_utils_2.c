/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:39:29 by dt                #+#    #+#             */
/*   Updated: 2025/10/02 21:00:56 by dt               ###   ########.fr       */
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

// if >0 is complex ==> returns how many ' / " are within one word
int	is_complex_wrd(int start_end[], char *input)
{
	int	qts;
	int	i;

	i = 0;
	qts = 0;
	while (i < start_end[1] - start_end[0])
	{
		if (input[start_end[0] + i] == '\'' || input[start_end[0] + i] == '"')
			qts++;
		i++;
	}
	return (qts);
}

// think about how to dollar expand if $ENV in the ""
int	*tk_word(char *input, int res[4])
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
	res[3] = is_complex_wrd(res, input);
	if (res[3] != 0)
		res[2] = TOKEN_COMPLEX;
	else
		res[2] = TOKEN_WORD;
	return (res);
}

// THE MAIN POINT IS TO DO RIGHT START_END[] FOR THE QUOTS FUNCS!! then dolla expand

// adjust for complex words:
// check if there are any of '...'/"..."/..wrds right after the second '


int	*tk_s_quotes(char *input, int res[4])
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
			res[2] = TOKEN_SG_Q;
		}
		else if (*input == '\'' && inword)
		{
			res[1] = i;
			break ;
		}
		input++;
		i++;
	}
	res[3] = is_complex_wrd(res, input);
	if (res[3] != 0)
		res[2] = TOKEN_COMPLEX;
	return (res);
}

int	*tk_d_quotes(char *input, int res[4])
{
	int	i;
	int	inqt_s;
	int	inword;

	i = 0;
	inword = 1;
	while (*input != '\0' && *input != ' ' && *input != '	')
	{
		if (*input == '"' && !inword)
		{
			inword = 1;
			res[0] = i + 1;
			res[2] = TOKEN_DB_Q;
		}
		else if (*input == '"' && inword && (*(input + 1) == '\0' || *(input
						+ 1) == '>' || *(input + 1) == '<') || *(input
					+ 1) == ' ' || *(input + 1) == '	')
		{
			res[1] = i;
			break ;
		}
		else if (*input == ' ' || *input == '	' || *input == '>'
				|| *input == '<')
			break;
		input++;
		i++;
	}
	res[3] = is_complex_wrd(res, input);
	if (res[3] != 0)
		res[2] = TOKEN_COMPLEX;
	return (res);
}

// adjust for complex words:
// think about how to dollar expand if $ENV in the ""
// check if there are any of '...'/"..."/..wrds right after the second "
// int	*tk_d_quotes(char *input, int res[4])
// {
// 	int	i;
// 	int	inword;

// 	i = 0;
// 	inword = 0;
// 	while (*input != '\0')
// 	{
// 		if (*input == '"' && !inword)
// 		{
// 			inword = 1;
// 			res[0] = i + 1;
// 			res[2] = TOKEN_DB_Q;
// 		}
// 		else if (*input == '"' && inword)
// 		{
// 			res[1] = i; //..
// 			break ;
// 		}
// 		input++;
// 		i++;
// 	}
// 	res[3] = is_complex_wrd(res, input);
// 	if (res[3] != 0)
// 		res[2] = TOKEN_COMPLEX;
// 	return (res);
// }