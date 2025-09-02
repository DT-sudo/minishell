/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:50:50 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/16 23:52:49 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exit_command_implementation(t_env *my_env)
{
    // Free the environment variables
    if (my_env)
    {
        free(my_env->key);
        free(my_env->value);
        free(my_env);
    }

    // Exit the program
    ft_printf("Exiting minishell...\n");
    exit(0);
}