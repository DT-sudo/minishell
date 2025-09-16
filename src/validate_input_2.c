/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:44:09 by dt                #+#    #+#             */
/*   Updated: 2025/08/29 08:43:19 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_sq(char *input, int *signl_q)
{
	int	i;

	i = 1;
	input++;
	while (*input != '\'' && *input != '\0')
	{
		input++;
		i++;
	}
	if (*input != '\'')
		*signl_q = 0;
	return (i + 1);
}

int	find_dq(char *input, int *double_q)
{
	int	i;

	i = 1;
	input++;
	while (*input != '"' && *input != '\0')
	{
		input++;
		i++;
	}
	if (*input != '"')
		*double_q = 0;
	return (i + 1);
}

int	has_unclosed_quotes(char *input)
{
	int	singl_q;
	int	double_q;

	singl_q = 1;
	double_q = 1;
	while (*input != '\0')
	{
		if (*input == '\'')
			input += find_sq(input, &singl_q);
		else if (*input == '"')
			input += find_dq(input, &double_q);
		else
			input++;
	}
	if (singl_q && double_q)
		return (0);
	return (1);
}

bool	drop_false(char *error_message)
{
	printf("%s\n", error_message);
	return (false);
}

// int has_wildcards(char *input)
// {
// 	if (*input == && *input == )

// 	return(1);
// }
