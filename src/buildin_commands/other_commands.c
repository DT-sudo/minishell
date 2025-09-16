/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:27:45 by olcherno          #+#    #+#             */
/*   Updated: 2025/08/31 21:33:06 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char **the_full_path_to_the_command(t_env *env)
{
    char *full_path;
    char *valuepath;
    t_env *tmp;

    tmp = env;
    while(tmp!=NULL)
    {
        if (ft_strcmp(tmp->key, "PATH") == 0)
            valuepath=tmp->value;
        tmp=tmp->next;
    }
    full_path=ft_split(valuepath, ':');
    

    return (full_path);

}



int other_commands_implementation(t_input *input, t_env *env)
{
    char **array_env;
    char **path;


    path=the_full_path_to_the_command(env);
    
    int i = 0;
    while (path && path[i])
    {
        printf("%s\n", path[i]);
        i++;
    }

    // if ( execve(input->word, input->argv, env) != 0)
    // return(1);
        //execve(path, input->argv, array_env);
   // printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("it`s only ls\n");
    return 0;
}
