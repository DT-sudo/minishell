/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/07/26 19:11:39 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*make_word(t_input *words, char *input)
{
	size_t	wrd_len;
    size_t i;

    i = 0;
	wrd_len = ft_strlen(input);
    words->word = malloc((wrd_len + 1)* (sizeof(char)));
    if (words->word == NULL)
        exit (2);
    while(i <= (wrd_len) && input[i])
    {
        words->word[i] = input[i];
        i++;
    }
    words->word[i] = '\0';
    words->next = NULL;
	return (words);
}

void	parse_input(t_input *words, char *input)
{
    int i = 0;
    
    t_input *tmp;
    bool first_wrd = 1;
    
	if (input == NULL)
		return ;
	while (*input != '\0')
	{
		if (*input != 32)
		{
            if (first_wrd)
            {
                tmp = make_word(words, input);
                first_wrd = 0;
            }
            else
            {
                tmp->next = make_word(words, input);
                tmp = tmp->next;    
            }
            input += ft_strlen(input);
        }
		else
			input++;
	}
    while(words->next != NULL)
    {
        printf("\nWord #%d: %s", i, words->word);
        i++;
    }
}
