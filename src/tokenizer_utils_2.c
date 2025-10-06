/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:39:29 by dt                #+#    #+#             */
/*   Updated: 2025/10/06 21:56:13 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// THE MAIN POINT IS TO DO  redo do_node func,
// redo tk_len_calc_len
// do dolla expand (think about how to dollar expand if $ENV in the "")

int	calc_len(t_input *new_word)
{
	int	len;

	len = 0;
	while (new_word->word[len] != '\0')
		len++;
	return (len);
}
// creat similar version for do_node quot skipping

// cahnges value of inqouts, q_type
// calcs how many inquoted quots (that should be printed) in the word

int	quote_setter(char cr, int inquots)
{
	static t_quote_state	chr = {0, 0, 0};
	
	if ((cr == '\'' || cr == '"'))
	{
		if (!chr.inquotes)
		{
			chr.to_kill = 0;
			chr.inquotes = 1;
			chr.type = cr;
			return (1);
		}
		else if (cr == chr.type)
		{
			chr.to_kill = 1;
			chr.inquotes = 0;
			chr.type = 0;
		}
	}
	return (0);
}
// if >0 is complex ==> returns how many ',
// " outter(that shouldnt be printed) are within one word
int	is_complex_wrd(t_len_type_qts *ltq, char *input, int inquots)
{
	int i;
	int	q;
	
	i = 0;
	q = 0;
	while (i++ < ltq->len && input)
	{
		if (quote_setter(*input, inquots))
			q += 2;
		input++;
	}
	return (q);
}

// NEW logic WOW!!!
t_len_type_qts	*tk_word(char *input,  t_len_type_qts *ltq)
{
	int		i;
	int		inquots;
	char	*tmp_input;

	i = 0;
	inquots = 0;
	tmp_input = input;
	while (*tmp_input)
	{
		inquots = quote_setter(*tmp_input, inquots);
		if (*tmp_input == ' ' || *tmp_input == '	' || *tmp_input == '>'
				|| *tmp_input == '<' || *tmp_input == '|' && !inquots)
			break ;
		i++;	
		tmp_input++;
	}
	ltq->len = --i;
	ltq->qts = is_complex_wrd(ltq, tmp_input, inquots);
	if (input[0] == '"' && input[i] == '"' && ltq->qts <= 2)
		ltq->type = TOKEN_DB_Q;
	else if (input[0] == '\'' && input[i] == '\'' && ltq->qts <= 2)
		ltq->type = TOKEN_SG_Q;
	if (ltq->qts)
		ltq->type = TOKEN_COMPLEX;
	return (ltq);
}
