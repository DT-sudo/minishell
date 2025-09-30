/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/28 18:16:13 by dt               ###   ########.fr       */
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

char	**dollar_expand(char **input, t_env **env)
{
	int		i;
	char	*env_value;
	char	*new_str;

	i = 1;
	while (input[i] != NULL)
	{
		if (ft_strncmp(input[i], "$", 1) == 0 && ft_strlen(input[i]) > 1)
		{
			if (ft_strcmp(input[i], "$?") == 0)
			{
				new_str = ft_itoa(exit_status);
				free(input[i]);
				input[i] = new_str;
			}
			else
			{
				env_value = get_env_value(input[i] + 1, env);
				if (env_value)
				{
					new_str = ft_strdup(env_value);
					free(input[i]);
					input[i] = new_str;
				}
				else
				{
					free(input[i]);
					input[i] = ft_strdup("");
				}
			}
		}
		i++;
	}
	return (input);
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
    (*cmnd_list)->argv = dollar_expand((*cmnd_list)->argv, env);
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

// char	*creat_str(char *str, char *wrd,  int flag, t_cmnd *next_wrd)
// {
// 	int		i;
// 	char	*res;
//     int size;
// 	i = 0;
// 	size = (int)ft_strlen(str) + (int)ft_strlen(wrd)+ flag + 1;
// 	if ((int)ft_strlen(wrd) != 0)
// 		size++;
// 	res = malloc(sizeof(char) * size);
// 	while (i < (int)ft_strlen(res) && str[i])
//     {
// 		res[i] = str[i];	
//         i++;
//     }
// 	if (ft_strlen(wrd))
// 	{
// 		res[i] = ' ';
// 		i = 0;
// 		while (i < (int)ft_strlen(wrd) && wrd[i])
//         {
//             ++i;
// 			res[i + (int)ft_strlen(str)] = wrd[i - 1];
//         }
// 	}
// 	if (flag && next_wrd == NULL) 
// 		res[++i + (int)ft_strlen(str)] = '\n';
// 	res[++i + (int)ft_strlen(str)] = '\0';
// 	return (res);
// }
// fun to culc len of all the cmnd before >.>>.<.|
// int	echo_command_implementation(t_cmnd **cmnd_list, t_env **env)
// {
// 	int		y;
// 	int		flag;
// 	char	*res;
// 	char	*res_tmp;
// 	t_cmnd	*input;
// 	y = 1;
// 	res = "";
// 	flag = 1;
// 	input = *cmnd_list;
// 	if (input->argv[1] && ft_strncmp(input->argv[1], "-n", 3) == 0)
// 	{
// 		flag = 0;
// 		y = 2;
// 	}
// 	if ((*cmnd_list)->heredoc)
// 	{ // make in one line func
// 		printf("error message");
// 		return(-1);
// 	}
// 	input->argv = dollar_expand(input->argv, env); // <-..
// 	while (input->argv[y] != NULL && !(*input->argv_type[y] >= TOKEN_PIPE
// 			&& *input->argv_type[y] <= TOKEN_HERE))
// 	{
// 		res_tmp = res;
// 		res = creat_str(res, input->argv[y++], flag, input->next);
// 		if (*res_tmp != '\0')
// 			free(res_tmp);
// 	}
// 	if (!(print_res(res, input->argv_type[y], flag))) 
// 		printf("%s", res);
// 	return (0);
// }
