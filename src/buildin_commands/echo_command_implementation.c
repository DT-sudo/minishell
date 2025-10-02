/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/30 20:08:03 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *input, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, input) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int echo_command_implementation(t_cmnd **cmnd_list, t_env **env)
{
    int	i;
    int y;
	int	n_FLAG;
    
	n_FLAG = 0;
	i = 1;
    y = 1;
	if ((*cmnd_list)->argv[i] && ft_strncmp((*cmnd_list)->argv[1], "-n", 3) == 0)
	{
		n_FLAG = 1;
        y = 2;
	}
    while ((*cmnd_list)->argv[y] != NULL)
    {
        printf("%s", (*cmnd_list)->argv[y]);
        if ((*cmnd_list)->argv[y + 1])
            printf(" ");
        y++;
    }
    if (n_FLAG == 0)
        printf("\n");
    return (0);
}


// char	**dollar_expand(char **input, t_env **env)
// {
// 	int		i;
// 	char	*env_value;
// 	char	*new_str;

// 	i = 1;
// 	while (input[i] != NULL)
// 	{
// 		if (ft_strncmp(input[i], "$", 1) == 0 && ft_strlen(input[i]) > 1) //add condition of "" and reg $
// 		{
// 			if (ft_strcmp(input[i], "$?") == 0)
// 			{
// 				new_str = ft_itoa(exit_status);
// 				free(input[i]);
// 				input[i] = new_str;
// 			}
// 			else
// 			{
// 				env_value = get_env_value(input[i] + 1, env);
// 				if (env_value)
// 				{
// 					new_str = ft_strdup(env_value);
// 					free(input[i]);
// 					input[i] = new_str;
// 				}
// 				else
// 				{
// 					free(input[i]);
// 					input[i] = ft_strdup("");
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	return (input);
// }