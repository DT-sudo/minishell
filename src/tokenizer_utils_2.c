/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:39:29 by dt                #+#    #+#             */
/*   Updated: 2025/10/03 23:43:54 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// THE MAIN POINT IS TO DO  redo do_node func,
// adjust every tk func res[0] then dolla expand
// also: check if we even needed in res[0] == 0... For now I think no.
// think about how to dollar expand if $ENV in the ""

int	calc_len(t_input *new_word)
{
	int	len;

	len = 0;
	while (new_word->word[len] != '\0')
		len++;
	return (len);
}
// cahnges value of inqouts, q_type 
// calcs how many inquoted quots (that should be printed) in the word
int	quote_setter(char *input, int inquots)
{
	char *q_type;
	
	q_type = '\0';
	if (*input == '\'' && !inquots && q_type == '\0')
	{
		*q_type = '\'';
		return (-1);
	}
	else if (*input == '"' && !inquots && q_type == '\0')
	{
		*q_type = '"';
		return (-1);
	}
	else if (*input == '"' && inquots && q_type == '"')
	{
		*q_type = '\0';
		return (1);
	}
	else if (*input == '\'' && inquots && q_type == '\'')
	{
		*q_type = '\0';
		return (1);
	}
	return (-1);
}

// if >0 is complex ==> returns how many ',
// " outter(that shouldnt be printed) are within one word
int	is_complex_wrd(int start_end[], char *tmp_input)
{
	int		q;

	q = 0;
	while (i++ < start_end[1] && tmp_input)
	{
		if (quote_setter(tmp_input, inquots))
			q += 2;
		tmp_input++;
	}
	return (q);
}

// NEW logic WOW!!!
// move size for the tmp_input is + start_end[1])
// word starts i[0] so outer quots should be remuved in do_node
// make func that detects which quots should be del within final word.
int	*tk_word(char *input, int res[4])
{
	int		i;
	int		inquots;
	char	*tmp_input;

	i = 0;
	res[0] = 0; //del
	inquots = 0;
	tmp_input = input;
	while (tmp_input)
	{
		inquots = quote_setter(tmp_input, inquots);
		if (*tmp_input == ' ' || *tmp_input == '	' || *tmp_input == '>' || *tmp_input == '<'
				|| *tmp_input == '|' && !inquots)
			break ;
		tmp_input++;
		i++;
	}
	res[1] = --i;
	res[3] = is_complex_wrd(res, tmp_input);
	// "case"
	if (input[0] == '"' && input[i] == '"' && res[3] <= 2)
		res[2] = TOKEN_DB_Q;
	else if (input[0] == '\'' && input[i] == '\'' && res[3] <= 2)
		res[2] = TOKEN_SG_Q;
!	if (res[3] )
		res[2] = TOKEN_COMPLEX;
	return (res);
}
