/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/03 15:04:01 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input	*do_node(int start_end[], char *input)
{
	int		i;
	int		j;
	int		len;
	char	*res;
	t_input	*new_node;

	i = 0;
	j = 0;
	new_node = malloc(sizeof(t_input));
	if (new_node == NULL || !input) // input?
		return (NULL);
	len = start_end[1] - start_end[0] - start_end[3]; // s_e[3] == 0 or > 0
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
	{
		// probably should be added free(words) if (words != NULL)
		free(new_node);
		return (NULL);
	}
	while (i < len)
	{
		if ((input[start_end[0] + j]) == '\'' || (input[start_end[0]
			+ j]) == '"')
		{
			j++;
			continue ;
		}
		res[i] = input[start_end[0] + j];
		i++;
		j++;
	}
	res[len] = '\0';
	new_node->word = res;
	new_node->next = NULL;
	if (start_end[3])
		new_node->type = 9;
	else
		new_node->type = start_end[2];
	return (new_node);
}

// return int that show how pointer in the OG input str should be moved ahead
// decides how to switche the pointer in input, with word type and res[3]
int	tk_len_calc_len(t_input *new_word, int res[])
{
	//+2?? check how would be calculated length for the complextype with "/' at the start
	if (new_word->type == 0 || new_word->type == 3 || new_word->type == 4
		|| new_word->type == 5 || new_word->type == 6 || new_word->type == 7
		|| new_word->type == 8)
		return (calc_len(new_word));
	else if (new_word->type == 1 || new_word->type == 2)
		return ((calc_len(new_word)) + 2);
	else if (new_word->type == 9)
		return (calc_len(new_word) + res[3]);
	return (0);
}
// return len of the new t_input word node
int	add_node(t_input **words, t_input *new_word, int res[])
{
	t_input	*tmp;

	if (*words == NULL)
	{
		*words = new_word;
		return (tk_len_calc_len(new_word, res));
	}
	tmp = *words;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_word;
	return (tk_len_calc_len(new_word, res));
}

int	creat_tokenz(char *input, t_input **words)
{
	int	type;
	int	res[4];
	int	len;

	if (*input == 124) // |
		return (add_node(words, do_node(tk_pipe(input, res), input), res));
	else if (*input == 36) // $
		return (add_node(words, do_node(tk_envp_v(input, res), input), res));
	else if (*input == 62) // >
		return (add_node(words, do_node(tk_out_appnd(input, res), input), res));
	else if (*input == 60) // <
		return (add_node(words, do_node(tk_in_here(input, res), input), res));
	else //  words -f , ' or  " 
		return (add_node(words, do_node(tk_word(input, res), input), res));
	return (0);
}

t_input	*tokenize(t_input *words, char *input)
{
	while (*input)
	{
		if (*input != 32 && *input != 9)
			input += creat_tokenz(input, &words);
		else
			input++;
	}
	// expand dollar do it after words creation
	return (words);
}

// dollar_expand(do_node(tk...), **evn)
// void	dollar_expand(t_input *node, t_env **env)
// {
// 	t_input *tmp;

// 	if (!node)
// 		return ;
// 	if (node->type == 0 || node->type == 2 || node->type == 8 )
// 2 for ".."/ 8 for $
// 	{
// 		// node->word;
// 	}
// }