/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation_copy.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/19 19:02:14 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// while != >> | > | << | <
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

// make pole for argv stats for tokens?/words? for $expanding and changing the argv[].
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

void	decide_tt(t_cmnd **cmnd_list)
{
	int	fd;

	if ((*cmnd_list)->rdr_in)
		fd = ;
	else if ((*cmnd_list)->appnd)
		;
	else if ((*cmnd_list)->rdr_out)
		;
	else if ((*cmnd_list)->pipe)
}

print_res(char *str, char *argv_type)
{
	
}

int decide_fd(char *str, char *argv_type)
{
	
}
char	*creat_str(char *str, char *wrd, int flag)
{
	int		res_len;
	int		wrd_len;
	int		i;
	char	*res;

	i = 0;
	res_len = (int)ft_strlen(res);
	wrd_len = (int)ft_strlen(wrd);
	size = res_len + wrd_len + 1 + flag;
	res = malloc(sizeof(char) * size);
	while (i < res_len && str[i])
		res[i++] = str[i];
	i = 1;
	while (i < wrd_len && wrd_len[i])
		res[i++ + res_len] = wrd_len[i];
	if (flag)
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}

// fun to culc len of all the cmnd before >.>>.<.|
int	echo_command_implementation(t_cmnd **cmnd_list, t_env **env)
{
	int		y;
	int		flag;
	char	*res;
	char	*res_tmp;
	t_cmnd	*input;

	input = *cmnd_list;
	flag = 0;
	y = 1;
	res = "";
	if (input->argv[1] && ft_strncmp(input->argv[1], "-n", 3) == 0)
	{
		flag = 1;
		y = 2;
	}
	if ((*cmnd_list)->heredoc)
	{ // make in one line func
		printf("error message");
		break ;
	}
	input->argv = dollar_expand(input->argv, env); // <-..
	while (input->argv[y] != NULL && !(input->argv_type[y] >= TOKEN_PIPE
			&& input->argv_type[y] <= TOKEN_HERE))
	{
		res_tmp = res;
		res = creat_str(res, input->argv[y++]);
		if (*res_tmp != "")
			free(res_tmp);
	}
	if (!(print_res(res, input->argv_type[y], flag)))
		printf("%s", res);
	return (0);
}

