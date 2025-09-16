/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/11 16:41:54 by dtereshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char* get_env_value(char *input, t_env **env)
{
    t_env *current = *env;
    while (current)
    {
        if (ft_strcmp(current->key, input) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

char **dollar_expand(char **input, t_env **env)
{
    int i;
    char *env_value;
    char *new_str;
    extern int exit_status;

    i = 1;
    while (input[i] != NULL)
    {
        if (ft_strncmp(input[i], "$", 1) == 0 && ft_strlen(input[i]) > 1)
        {
            //printf("DOLLAR EXPAND: %s\n", input[i]);
            if (ft_strcmp(input[i], "$?") == 0)
            {
                new_str = ft_itoa(exit_status);
                free(input[i]);
                input[i] = new_str;
            }
            else
            {
                env_value = get_env_value(input[i] + 1, env); // Skip the '$' character
                if (env_value)
                {
                    new_str = ft_strdup(env_value);
                    free(input[i]);
                    input[i] = new_str;
                }
                else
                {
                    free(input[i]);
                    input[i] = ft_strdup(""); // Replace with empty string if not found 
                }
            }
        }
        i++;
    }
    return input;
}

int echo_command_implementation(char **input, t_env **env)
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
    input = dollar_expand(input, env);  // Put this back!
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