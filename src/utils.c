/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/08/31 21:00:16 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// clean stack func needed 
void ft_clean(t_input *words, char *input)
{
	if (input)
		free(input);
	if (words->word)
		free(words->word);
	if (words)
		free(words);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		exit(1);
	while (*s != '\0' && *s != 32)
	{
		i++;
		s++;
	}
	return (i);
}
