/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/31 22:53:50 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo_command_implementation(char **input)
{
    int	i;
    int y;
	int	n_FLAG;
    
	n_FLAG = 0;
	i = 1;
    y = 1;
	if (input[i] && ft_strncmp(input[1], "-n", 3) == 0)
	{
		n_FLAG = 1;
        y = 2;
	}

    while (input[y] != NULL)
    {
        printf("%s", input[y]);
        if (input[y + 1])
            printf(" ");
        y++;
    }
    if (n_FLAG == 0)
    {
        printf("\n");
    }
    return (0);
}


    // printf("%s", input->argv[2]);
    // char *argv[] = {"echo", "-n", "ASD","ASD","ASD", NULL};
    // ft_printf("%s", argv[0]);
    // if (ft_strncmp(input->argv[1], "$", 2) == 0)
    // {
    //     return (dollar_expand(input->argv, input->word));
    // }

    // while (input->argv[i] != NULL)
    // {
    //     ft_printf("%s", input->argv[i]);
    //     if (input->argv[i + 1] != NULL)
    //         ft_printf(" ");
    //     i++;
    // }
        // if (input->argv[i]!= NULL && ft_strncmp(input->argv[1], "$", 1) == 0) //should be changed by env in parsing
    // {
    //     return (dollar_expand(input->argv, input->word));
    // }