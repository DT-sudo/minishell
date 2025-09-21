/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command_implementation_copy.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:26:59 by olcherno          #+#    #+#             */
/*   Updated: 2025/09/21 18:16:12 by dt               ###   ########.fr       */
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

// prints needed str to needed fd any way, returns int 0 if echo not complex
// int 1 if complex -> has |, >, >>, <. ->  
// (print_res(res, input->argv_type[y], flag))
int print_res(char *str, char *argv_type, int flag)
{
	int fd;
	
	//echo not complex
	if (argv_type == NULL)
		return 0;
	fd = decide_fd(argv_type);
	// 1. open file, get fd
	// 2. write to the needed fd
}
int decide_fd(char *str, char *argv_type)
{
	if (argv_type == TOKEN_PIPE)
		return ;
	else if (argv_type == TOKEN_RDR_IN)
		return ;
	else if (argv_type == TOKEN_RDR_OUT)
		return ;
	else if (argv_type == TOKEN_APPND)
		return ;
}

char	*creat_str(char *str, char *wrd,  int flag, t_cmnd *next_wrd)
{
	int		i;
	char	*res;

	i = 0;
	size = (int)ft_strlen(str) + (int)ft_strlen(wrd)+ flag + 1;
	if ((int)ft_strlen(wrd) != 0)
		size++;
	res = malloc(sizeof(char) * size);
	while (i < (int)ft_strlen(res) && str[i])
		res[i++] = str[i];	
	if (ft_strlen(wrd))
	{
		res[i] = ' ';
		i = 0;
		while (i < (int)ft_strlen(wrd) && wrd[i])
			res[++i + (int)ft_strlen(str)] = wrd[i];
	}
	if (flag && next_wrd == NULL) 
		res[++i + (int)ft_strlen(str)] = '\n';
	res[++i + (int)ft_strlen(str)] = '\0';
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

	y = 1;
	res = "";
	flag = 1;
	input = *cmnd_list;
	if (input->argv[1] && ft_strncmp(input->argv[1], "-n", 3) == 0)
	{
		flag = 0;
		y = 2;
	}
	if ((*cmnd_list)->heredoc)
	{ // make in one line func
		printf("error message");
		return(-1);
	}
	input->argv = dollar_expand(input->argv, env); // <-..
	while (input->argv[y] != NULL && !(input->argv_type[y] >= TOKEN_PIPE
			&& input->argv_type[y] <= TOKEN_HERE))
	{
		res_tmp = res;
		res = creat_str(res, input->argv[y++], flag, input->next);
		if (*res_tmp != "")
			free(res_tmp);
	}
	if (!(print_res(res, input->argv_type[y], flag))) 
		printf("%s", res);
	return (0);
}

