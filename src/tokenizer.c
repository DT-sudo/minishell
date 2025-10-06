/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/06 21:54:27 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quote_state	detec_inquotes(char cr)
{
	static t_quote_state	chr = {0, 0, 0};
	
	if ((cr == '\'' || cr == '"'))
	{
		if (!chr.inquotes)
		{
			chr.to_kill = 0;
			chr.inquotes = 1;
			chr.type = cr;
		}
		else if (cr == chr.type)
		{
			chr.to_kill = 1;
			chr.inquotes = 0;
			chr.type = 0;
		}
	}
	return (chr);
}

// word starts i[0] so outer quots should be remuved in do_node
// make func that detects which quots should be del within final word.
// creat similar version for do_node quot skipping (quote_setter)
// so yeah very uninquoted qutes should be skiped (quote_setter)
t_input	*do_node(t_len_type_qts *ltq, char *input)
{
	int						i;
	char					*res;
	t_input					*new_node;
	static t_quote_state	state = {0, 0};

	i = 0;
	new_node = malloc(sizeof(t_input));
	if (new_node == NULL || !input)
		return (NULL);
	res = malloc(sizeof(char) * (ltq->len - ltq->qts + 1));
	if (res == NULL)
	{
		// probably should be added free(words) if (words != NULL)
		free(new_node);
		return (NULL);
	}
	while (input && i < (ltq->len - ltq->qts))
	{
		state = detec_inquotes(*input);
		if (state.inquotes && state.type == *input && state.to_kill)
			input++;
		else
			res[i++] = *input++;
	}
	res[(ltq->len - ltq->qts)] = '\0';
	new_node->word = res;
	new_node->next = NULL;
	if (ltq->qts)
		new_node->type = TOKEN_COMPLEX;
	else
		new_node->type = ltq->type;
	return (new_node);
}

void	add_node(t_input **words, t_input *new_word, t_len_type_qts *ltq)
{
	t_input	*tmp;

	if (*words == NULL)
		*words = new_word;
	tmp = *words;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_word;
}

// data type to void
int	creat_tokenz(char *input, t_input **words)
{
	int	len;
	int	type;
	t_len_type_qts *ltq;

	ltq = malloc(sizeof(t_len_type_qts));
	if (!ltq)
		exit(1);
	if (*input == 124) // |
		add_node(words, do_node(tk_pipe(input, ltq), input), ltq);
	else if (*input == 62) // >
		add_node(words, do_node(tk_out_appnd(input, ltq), input), ltq);
	else if (*input == 60) // <
		add_node(words, do_node(tk_in_here(input, ltq), input), ltq);
	else //  words -f , ' or  "
		add_node(words, do_node(tk_word(input, ltq), input), ltq);
	free(ltq);
	return (0);
}

t_input	*tokenize(t_input *words, char *input)
{
	while (*input)
	{
		if (*input != 32 && *input != 9)
			creat_tokenz(input, &words);
		else
			input++;
	}
	// expand dollar do it after words creation
	return (words);
}
