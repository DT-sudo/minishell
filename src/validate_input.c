/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:30:48 by dt                #+#    #+#             */
/*   Updated: 2025/08/26 13:25:17 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//					FOR THIS PART
// 1. for flag tokenather add because -l-a is not valid format
// 2. add validation of more then 2 of '>' '<' in the raw
// 4. add digits validation
// 5. add validation of the empty - for flag tokenather
// 6. $lower_case is valid but just prints \n or just nothing if within ""

// 					FOR LINKED LIST validation
// 1. Pipe at start: | ls → syntax error.
// 2. Pipe at end: ls | → syntax error.
// 3. Pipe next to another pipe: ls | | wc → invalid, must catch.
// 4.

//   				For env vars $HOME...
// Shell variable names can only contain letters, digits,
// and underscores ([a-zA-Z0-9_])

// '\'
int	has_backslash(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (*input == 92 && !in_q)
			return (1);
		input++;
	}
	return (0);
}

// ';'
int	has_simocolon(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (*input == 59 && !in_q)
			return (1);
		input++;
	}
	return (0);
}

// || or &&
int	has_double_and_or_pipe(char *input)
{
	int	in_q;

	in_q = 0;
	while (*input != '\0')
	{
		if (*input == 34 && !in_q)
			in_q = 1;
		else if (*input == 39 && !in_q)
			in_q = 2;
		else if (*input == 34 && in_q == 1)
			in_q = 0;
		else if (*input == 39 && in_q == 2)
			in_q = 0;
		if (!in_q && (((*input == 38 && *(input + 1) == 38)) || (*input == 124
					&& *(input + 1) == 124)))
			return (1);
		input++;
	}
	return (0);
}

bool	validate_input(char *input)
{
	if (!input)
		return (false);
	if (has_unclosed_quotes(input))
		return (drop_false("Minishell:  syntax error: unclosed quotes\n"));
	if (has_backslash(input))
		return (drop_false("Minishell: syntax error: unexpected '\\'\n"));
	if (has_simocolon(input))
		return (drop_false("Minishell: syntax error: unexpected ';'\n"));
	if (has_double_and_or_pipe(input))
		return (drop_false("Minishell: syntax error: unexpected '&&' or '||' \n"));
	return (true);
}
