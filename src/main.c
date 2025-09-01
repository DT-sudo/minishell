/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/08/23 18:21:39 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// copy envp to stack and after that mutate the PATH when execv usiung it
// int	main(int argc, char **argv, char **envp)
int	main(void)
{
	t_input	*words;
	char	*input;
	int i;
	
	i = 0;
	words = NULL;
	while (42)
	{
		input = readline("Minishell % ");
		if (input == NULL)
			break ;
		if (*input == '\0' || !validate_input(input))
		{
			free(input);
			continue ;
		}
		words = tokenize(words, input);
		while(words != NULL)
		{
			i += 1;
			printf("\n#%d. word: %s, type %d", i, words->word, words->type);
			words = words->next;
		}
		printf("\n");
	}
	return (0);
}
