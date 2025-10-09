/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/09 18:45:53 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// every uninquoted qutes should be skipped
t_input	*do_node(t_len_type_qts *ltq, char *input)
{
	int				i;
	char			*res;
	t_input			*new_node;
	t_quote_state	*state;

	i = 0;
	state = NULL;
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
		state = dtct_inquotes(*input);
		if ((state->inquotes && state->type == *input) || state->closed)
			input++;
		else
			res[i++] = *input++;
	}
	res[i] = '\0';
	new_node->word = res;
	new_node->next = NULL;
	if (ltq->qts)
		new_node->type = TOKEN_COMPLEX;
	else
		new_node->type = ltq->type;
	reset_state_sttc(state);
	return (new_node);
}

void	add_node(t_input **words, t_input *new_word)
{
	t_input	*tmp;

	if (!words || !new_word)
		return;
	if (*words == NULL)
	{
		*words = new_word;
		return;
	}
	tmp = *words;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_word;
}

// returns length of 
int	creat_tokenz(char *input, t_input **words)
{
	t_len_type_qts	*ltq;
	int				cnsmd;

	ltq = malloc(sizeof(t_len_type_qts));
	if (!ltq)
		exit(1);
	ltq->qts = 0;
	ltq->len = 0;
	ltq->type = -1;
	if (*input == 124) // |
		add_node(words, do_node(tk_pipe(input, ltq), input));
	else if (*input == 62) // >
		add_node(words, do_node(tk_out_appnd(input, ltq), input));
	else if (*input == 60) // <
		add_node(words, do_node(tk_in_here(input, ltq), input));
	else //  words
		add_node(words, do_node(tk_word(input, ltq), input));
	cnsmd = ltq->len;
	free(ltq);
	return (cnsmd);
}

t_input	*tokenize(t_input *words, char *input)
{
	int res;

	res = 0;
	while (*input)
	{
		// write(1, "d", 1);
		if (*input != ' ' && *input != '\t')
		{
			res = creat_tokenz(input, &words);
            input += res;                           
		}
		else
			input++;
	}
	return (words);
}
;